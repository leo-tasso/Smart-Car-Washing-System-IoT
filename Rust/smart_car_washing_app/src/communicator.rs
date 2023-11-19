use serialport::SerialPort;

pub struct Communicator {
    temp: f32,
    connected: bool,
    maintenance_req: bool,
    active_scenario: String,
    connected_port: Option<Box<dyn SerialPort>>,
    selected_port: Option<String>,
}

impl Default for Communicator {
    fn default() -> Self {
        Self {
            temp: 0.0,
            connected: false,
            maintenance_req: false,
            active_scenario: "".to_string(),
            connected_port: None,
            selected_port: None,
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
        self.connected
    }
    pub fn maintenance_req(&self) -> bool {
        self.maintenance_req
    }
    pub fn active_scenario(&self) -> &str {
        &self.active_scenario
    }
    pub fn connected_port(&self) -> &Option<Box<dyn SerialPort>> {
        &self.connected_port
    }

    pub fn set_selected_port(&mut self, selected_port: Option<String>) {
        self.selected_port = selected_port;
    }
    pub fn connect(&mut self){
    }
}