#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]
extern crate serde;
extern crate egui_gauge;
extern crate eframe;
extern crate serialport;

use communicator::Communicator;
use crate::app::SmartCarWashingApp;
mod app;
mod communicator;

fn main() -> eframe::Result<()> {
    env_logger::init(); // Log to stderr (if you run with `RUST_LOG=debug`).

    let native_options = eframe::NativeOptions {
        initial_window_size: Some([400.0, 300.0].into()),
        min_window_size: Some([300.0, 220.0].into()),
        ..Default::default()
    };


    let ports = serialport::available_ports().expect("No ports found!");
    for p in ports {
        println!("{}", p.port_name);
    }

    let communicator = Communicator::new();

    eframe::run_native(
        "eframe template",
        native_options,
        Box::new(|cc| Box::new(SmartCarWashingApp::new(cc, communicator))),
    )
}