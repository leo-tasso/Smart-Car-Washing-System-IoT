use eframe::epaint::mutex::Mutex;
use json::parse;
use serialport::SerialPort;
use std::io::{Read, Write};
use std::sync::Arc;
use std::thread;
use egui::TextBuffer;

pub struct InnerCommunicator {
    temp: f32,
    washing_percentage: i8,
    car_in_check_in: bool,
    car_in_washing: bool,
    gate_open: bool,
    washing: bool,
    maintenance_req: bool,
    connected_port: Option<Box<dyn SerialPort>>,
}

pub struct Communicator {
    inner: Arc<Mutex<InnerCommunicator>>,
    read_thread: Option<thread::JoinHandle<()>>,
    stop_flag: Arc<Mutex<bool>>,

}

impl Default for Communicator {
    fn default() -> Self {
        Self {
            inner: Arc::new(Mutex::new(InnerCommunicator {
                temp: 0.0,
                washing_percentage: 0,
                car_in_check_in: false,
                car_in_washing: false,
                gate_open: false,
                washing: false,
                maintenance_req: false,
                connected_port: None,
            })),
            read_thread: None,
            stop_flag: Arc::new(Mutex::new(false)),
        }
    }
}
impl Communicator {
    pub fn new() -> Self {
        Default::default()
    }

    pub fn temp(&self) -> f32 {
        self.inner.lock().temp
    }
    pub fn connected(&self) -> bool {
        self.inner.lock().connected_port.is_some()
    }
    pub fn maintenance_req(&self) -> bool {
        self.inner.lock().maintenance_req
    }

    pub fn car_in_check_in(&self) -> bool { self.inner.lock().car_in_check_in   }

    pub fn car_in_washing(&self) -> bool {
        self.inner.lock().car_in_washing
    }

    pub fn gate_open(&self) -> bool {
        self.inner.lock().gate_open
    }

    pub fn washing(&self) -> bool {
        self.inner.lock().washing
    }

    pub fn washing_percentage(&self) -> i8 {
        self.inner.lock().washing_percentage
    }


    pub fn connect(&mut self, path: String) {
        *self.stop_flag.lock() = false;
        let local_self = self.inner.clone();
        local_self.lock().connected_port = Some(
            serialport::new(path, 9600)
                .open()
                .expect("Failed to open port"),
        );
        /*
        thread::spawn(move || loop {
            if !local_self.lock().connected_port.is_some() {break;}
            local_self.lock().connected_port.as_mut().unwrap()
                .write_all("Hello world".as_bytes())
                .expect("Failed to write to serial port");
            thread::sleep(Duration::from_millis(1000));
        });
        let local_self = self.inner.clone();*/
        let stop_flag_clone = Arc::clone(&self.stop_flag);
        let mut cloned_port = local_self
            .lock()
            .connected_port
            .as_mut()
            .unwrap()
            .try_clone()
            .unwrap();
        let mut serial_buffer: Vec<u8> = Vec::new();
        let mut buffer: [u8; 1] = [0; 1];
        self.read_thread = Option::from(thread::spawn(move || loop {
            if *stop_flag_clone.lock() { break; }
            match cloned_port.read(&mut buffer) {
                Ok(bytes_read) => {
                    if bytes_read > 0 {
                        serial_buffer.push(buffer[0]);
                        // Check if you have received a complete message
                        if buffer[0] == b'\n' {
                            // Process the received message (in serial_buffer)
                            let received_message = String::from_utf8_lossy(&serial_buffer);
                            println!("Received: {}", received_message);

                            if let Ok(res_json) = parse(received_message.as_str()) {
                                //local_self.lock().temp = res_json["Temp"].as_f32().unwrap()
                                //println!("Parsed: {:#?}", res_json);
                                match res_json["temp"].as_f32() {
                                    None => {}
                                    Some(t) => { local_self.lock().temp = t }
                                }
                                match res_json["carInCheckIn"].as_bool() {
                                    None => {}
                                    Some(t) => { local_self.lock().car_in_check_in = t }
                                }
                                match res_json["carInWashingArea"].as_bool() {
                                    None => {}
                                    Some(t) => { local_self.lock().car_in_washing = t }
                                }
                                match res_json["washing"].as_bool() {
                                    None => {}
                                    Some(t) => { local_self.lock().washing = t }
                                }
                                match res_json["gateOpen"].as_bool() {
                                    None => {}
                                    Some(t) => { local_self.lock().gate_open = t }
                                }
                                match res_json["washingPercentage"].as_i8() {
                                    None => {}
                                    Some(t) => { local_self.lock().washing_percentage = t }
                                }
                            }
                            // Clear the buffer for the next message
                            serial_buffer.clear();
                        }
                    }
                }
                Err(e) => {
                    eprintln!("Error reading from serial port: {}", e);
                    break;
                }
            }
        }));
    }
    pub fn stop(&mut self) {
        if self.inner.lock().connected_port.is_some() {
            *self.stop_flag.lock() = true;
            if let Some(handle) = self.read_thread.take() {
                handle.join().unwrap();
            }
            self.inner.lock().connected_port = None;
        }
    }

    pub fn maintenance_done(&mut self) {
        self.inner
            .lock()
            .connected_port
            .as_mut()
            .unwrap()
            .write_all("MaintenanceDone".as_bytes())
            .expect("Failed to write to serial port");
    }
}
