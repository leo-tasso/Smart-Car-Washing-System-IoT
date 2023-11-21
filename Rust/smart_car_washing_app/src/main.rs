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

    let icon = image::open("smartCarWash.png")
    .expect("Failed to open icon path")
    .to_rgba8();
let (icon_width, icon_height) = icon.dimensions();
    let native_options = eframe::NativeOptions {
        initial_window_size: Some([250.0, 330.0].into()),
        min_window_size: Some([250.0, 330.0].into()),
        max_window_size: Some([250.0, 330.0].into()),
        icon_data: Some(eframe::IconData {
            rgba: icon.into_raw(),
            width: icon_width,
            height: icon_height,
        }),
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