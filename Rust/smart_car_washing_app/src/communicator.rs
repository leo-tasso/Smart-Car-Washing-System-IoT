use serialport::SerialPort;
use std::time::Duration;
use std::{io, thread};


pub struct Communicator {
    temp: f32,
    maintenance_req: bool,
    active_scenario: String,
    connected_port: Option<Box<dyn SerialPort>>,
}

impl Default for Communicator {
    fn default() -> Self {
        Self {
            temp: 0.0,
            maintenance_req: false,
            active_scenario: "".to_string(),
            connected_port: None,
        }
    }
}
impl Communicator {
    pub fn new() -> Self {
        Default::default()
    }

    pub fn temp(&self) -> f32 {
        self.temp
    }
    pub fn connected(&self) -> bool {
        self.connected_port.is_some()
    }
    pub fn maintenance_req(&self) -> bool {
        self.maintenance_req
    }
    pub fn active_scenario(&self) -> &str {
        self.active_scenario.as_str()
    }

    pub fn connect(&mut self,path: String){
        self.connected_port = Some(serialport::new( path, 9600).open().expect("Failed to open port"));

        let mut clone = self.connected_port.as_mut()
        .unwrap()
        .try_clone().expect("Failed to clone");
        let running = self.connected_port.is_some();

        thread::spawn(move || loop {
            if !running {break;}
            clone
                .write_all(&[5, 6, 7, 8])
                .expect("Failed to write to serial port");
            thread::sleep(Duration::from_millis(1000));
        });
        let mut buffer: [u8; 1] = [0; 1];
        let mut clone = self.connected_port.as_mut()
        .unwrap()
        .try_clone().expect("Failed to clone");
        thread::spawn(move ||loop {
            if !running {break;}
            match clone.read(&mut buffer) {
                Ok(bytes) => {
                    if bytes == 1 {
                        println!("Received: {:?}", buffer);
                    }
                }
                Err(ref e) if e.kind() == io::ErrorKind::TimedOut => (),
                Err(e) => eprintln!("{:?}", e),
            }
        });
    }
    pub fn stop(&mut self){
        if self.connected_port.is_some() {
            self.connected_port = None;
        }
    }

    pub fn maintenance_done(&mut self){
        self.maintenance_req = false;
    }
}