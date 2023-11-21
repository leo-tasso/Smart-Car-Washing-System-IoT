use serialport::SerialPort;
use std::{io, thread};
use std::io::{Read, Write};
use std::str::from_utf8;
use std::sync::Arc;
use eframe::epaint::mutex::Mutex;
use json::{JsonValue, parse};

pub struct InnerCommunicator {
    temp: f32,
    maintenance_req: bool,
    active_scenario: String,
    connected_port: Option<Box<dyn SerialPort>>,
}

pub struct Communicator{
    inner: Arc<Mutex<InnerCommunicator>>
}

impl Default for Communicator {
    fn default() -> Self {
        Self {
            inner: Arc::new(Mutex::new(
                InnerCommunicator {
                    temp: 0.0,
                    maintenance_req: false,
                    active_scenario: "".to_string(),
                    connected_port: None,
                }))
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
    pub fn active_scenario(&self) -> String {
       self.inner.lock().active_scenario.clone()
    }

    pub fn connect(&mut self,path: String){
        let local_self = self.inner.clone();

       local_self.lock().connected_port = Some(serialport::new( path, 9600).open().expect("Failed to open port"));
/*
        thread::spawn(move || loop {
            if !local_self.lock().connected_port.is_some() {break;}
            local_self.lock().connected_port.as_mut().unwrap()
                .write_all("Hello world".as_bytes())
                .expect("Failed to write to serial port");
            thread::sleep(Duration::from_millis(1000));
        });
        let local_self = self.inner.clone();*/
        let mut cloned_port = local_self.lock().connected_port.as_mut().unwrap().try_clone().unwrap();
        let mut serial_buf: Vec<u8> = vec![0; 128];
        thread::spawn(move ||            loop {
            let mut json_res= JsonValue::Null;
            match cloned_port.read(serial_buf.as_mut_slice()) {
                Ok(t) => {
                    io::stdout().write_all(&serial_buf[..t]).unwrap();
                    json_res = parse(from_utf8(&serial_buf[..t]).expect("Error extracting string")).expect("Error parsing received text")
                },
                Err(ref e) if e.kind() == io::ErrorKind::TimedOut => (),
                Err(e) => eprintln!("{:?}", e),
            }
            local_self.lock().temp = json_res["Temp"].as_f32().expect("Error parsing Temp");
        });
    }
    pub fn stop(&mut self){
        if self.inner.lock().connected_port.is_some() {
            self.inner.lock().connected_port = None;
        }
    }

    pub fn maintenance_done(&mut self){
        self.inner.lock().maintenance_req = false;
    }
}