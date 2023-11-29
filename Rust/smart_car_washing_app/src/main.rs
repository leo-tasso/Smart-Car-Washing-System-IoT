#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]
extern crate serde;
extern crate egui_gauge;
extern crate eframe;
extern crate serialport;
extern crate json;
extern crate egui;

use egui::IconData;
use communicator::Communicator;
use crate::app::SmartCarWashingApp;
mod app;
mod communicator;

fn main() -> eframe::Result<()> {
    env_logger::init(); // Log to stderr (if you run with `RUST_LOG=debug`).

    let icon = image::open("res/smartCarWash.png")
    .expect("Failed to open icon path")
    .to_rgba8();
let (icon_width, icon_height) = icon.dimensions();
    let native_options = eframe::NativeOptions {
        viewport: egui::ViewportBuilder::default()
            .with_inner_size([300.0, 500.0])
            .with_min_inner_size([300.0, 500.0])
            .with_max_inner_size([300.0, 500.0])
            .with_icon(IconData {
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
        Box::new(|cc|{
            egui_extras::install_image_loaders(&cc.egui_ctx);
            Box::new(SmartCarWashingApp::new(cc, communicator))
        }),
    )
}