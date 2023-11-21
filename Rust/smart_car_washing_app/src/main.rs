#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]
extern crate serde;
extern crate egui_gauge;
extern crate eframe;
extern crate serialport;
extern crate json;

use communicator::Communicator;
use crate::app::SmartCarWashingApp;
mod app;
mod communicator;

fn main() -> eframe::Result<()> {
    env_logger::init(); // Log to stderr (if you run with `RUST_LOG=debug`).

    let native_options = eframe::NativeOptions {
        initial_window_size: Some([250.0, 330.0].into()),
        min_window_size: Some([250.0, 330.0].into()),
        max_window_size: Some([250.0, 330.0].into()),
        ..Default::default()
    };


    let ports = serialport::available_ports().expect("No ports found!");
    for p in ports {
        println!("{}", p.port_name);
    }

    let communicator = Communicator::new();

    eframe::run_native(
        "Smart CarWashing Console",
        native_options,
        Box::new(|cc|Box::new(SmartCarWashingApp::new(cc, communicator))),
    )
}