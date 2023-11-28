use communicator::Communicator;
use eframe::epaint::Color32;
use egui::vec2;
use egui_gauge::Gauge;

/// We derive Deserialize/Serialize so we can persist app state on shutdown.
#[derive(serde::Deserialize, serde::Serialize)]
#[serde(default)] // if we add new fields, give them default values when deserializing old state

pub struct SmartCarWashingApp {
    // Example stuff:
    label: String,

    #[serde(skip)] // This how you opt-out of serialization of a field
    temp: f32,
    #[serde(skip)] // This how you opt-out of serialization of a field
    selected_port: usize,
    #[serde(skip)] // This how you opt-out of serialization of a field
    communicator: Communicator,
}

impl Default for SmartCarWashingApp {
    fn default() -> Self {
        Self {
            // Example stuff:
            label: "Hello World!".to_owned(),
            temp: 2.7,
            selected_port: 1,
            communicator: Default::default(),
        }
    }
}

impl SmartCarWashingApp {
    /// Called once before the first frame.
    pub fn new(cc: &eframe::CreationContext<'_>, communicator: Communicator) -> Self {
        // This is also where you can customize the look and feel of egui using
        // `cc.egui_ctx.set_visuals` and `cc.egui_ctx.set_fonts`.

        // Load previous app state (if any).
        // Note that you must enable the `persistence` feature for this to work.
        if let Some(storage) = cc.storage {
            return eframe::get_value(storage, eframe::APP_KEY).unwrap_or_default();
        }
        Self {
            label: "".to_string(),
            temp: 0.0,
            selected_port: 0,
            communicator,
        }
    }
}

impl eframe::App for SmartCarWashingApp {
    /// Called each time the UI needs repainting, which may be many times per second.
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        // Put your widgets into a `SidePanel`, `TopPanel`, `CentralPanel`, `Window` or `Area`.
        // For inspiration and more examples, go to https://emilk.github.io/egui

        egui::TopBottomPanel::top("top_panel").show(ctx, |ui| {
            // The top panel is often a good place for a menu bar:

            egui::menu::bar(ui, |ui| {
                ui.menu_button("Menu", |ui| {
                    egui::widgets::global_dark_light_mode_buttons(ui);
                    if ui.button("Quit").clicked() {
                        ctx.send_viewport_cmd(egui::ViewportCommand::Close);
                    }
                });
                ui.add_space(16.0);
            });
        });

        egui::CentralPanel::default().show(ctx, |ui| {
            // The central panel the region left after adding TopPanel's and SidePanel's

            let mut alternatives: Vec<String> = match serialport::available_ports() {
                Ok(mut v) => v.iter_mut().map(|p| p.port_name.clone()).collect(),
                _ => {
                    vec!["No port Found".to_string()]
                }
            };
            if alternatives.is_empty() {
                alternatives.append(&mut vec!["No port found".to_string()]);
            }
            ui.label("Select serial port:");
            egui::ComboBox::from_label("").show_index(
                ui,
                &mut self.selected_port,
                alternatives.len(),
                |i| alternatives[i].clone(),
            );
            ui.horizontal(|ui| {
                if ui
                    .add_enabled(
                        !self.communicator.connected()
                            && serialport::available_ports().is_ok_and(|r| !r.is_empty()),
                        egui::Button::new("Connect"),
                    )
                    .clicked()
                {
                    self.communicator
                        .connect(alternatives[self.selected_port].clone());
                }

                if ui
                    .add_enabled(
                        self.communicator.connected(),
                        egui::Button::new("Disconnect"),
                    )
                    .clicked()
                {
                    self.communicator.stop()
                };
            });
            ui.horizontal(|ui| {
                ui.add(
                    if self.communicator.car_in_check_in() {
                    egui::Image::new(egui::include_image!("../res/car.png"))
                        .fit_to_fraction(vec2(7.0,7.0))}
                        else {                     egui::Image::new(egui::include_image!("../res/Empty.png"))
                            .fit_to_fraction(vec2(7.0,7.0))}
                );
                ui.add(
                    if self.communicator.gate_open() {
                        egui::Image::new(egui::include_image!("../res/open bar.png"))
                            .fit_to_fraction(vec2(1.0,1.0))}
                    else {                     egui::Image::new(egui::include_image!("../res/closed bar.png"))
                        .fit_to_fraction(vec2(1.0,1.0))}
                );
                ui.add(
                    if self.communicator.car_in_washing() {
                        egui::Image::new(egui::include_image!("../res/car.png"))
                            .fit_to_fraction(vec2(1.0,1.0))}
                    else {
                        egui::Image::new(egui::include_image!("../res/Empty.png"))
                        .fit_to_fraction(vec2(1.0,1.0))}
                );
                if self.communicator.washing() {
                    ui.add(
                        egui::Image::new(egui::include_image!("../res/water.png"))
                            .fit_to_fraction(vec2(1.0, 1.0))
                    );
                }
            });
            if ui
                .add_enabled(
                    self.communicator.connected() && self.communicator.maintenance_req(),
                    egui::Button::new("Maintenance done"),
                )
                .clicked()
            {
                self.communicator.maintenance_done();
            };
            /*ui.heading(
                "Active scenario: ".to_owned() + self.communicator.active_scenario().as_str(),
            );*/
            ui.add(
                Gauge::new(self.communicator.temp(), 0.0..=37.0, 200.0, Color32::GREEN)
                    .text("Sys Temp"),
            );
            ui.separator();

            ui.with_layout(egui::Layout::bottom_up(egui::Align::LEFT), |ui| {
                egui::warn_if_debug_build(ui);
            });
            ui.ctx().request_repaint();
        });
    }

    /// Called by the frame work to save state before shutdown.
    fn save(&mut self, storage: &mut dyn eframe::Storage) {
        eframe::set_value(storage, eframe::APP_KEY, self);
    }
}
