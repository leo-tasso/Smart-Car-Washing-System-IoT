use communicator::Communicator;
use eframe::epaint::Color32;
use egui_gauge::Gauge;

/// We derive Deserialize/Serialize so we can persist app state on shutdown.
#[derive(serde::Deserialize, serde::Serialize)]
#[serde(default)] // if we add new fields, give them default values when deserializing old state

pub struct SmartCarWashingApp {
    // Example stuff:
    label: String,

    #[serde(skip)] // This how you opt-out of serialization of a field
    temp: f32,
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
                {
                    ui.menu_button("File", |ui| {
                        if ui.button("Quit").clicked() {
                            _frame.close();
                        }
                    });
                    ui.add_space(16.0);
                }

                egui::widgets::global_dark_light_mode_buttons(ui);
            });
        });

        egui::CentralPanel::default().show(ctx, |ui| {
            // The central panel the region left after adding TopPanel's and SidePanel's
            ui.heading("eframe template");

            ui.horizontal(|ui| {
                ui.label("Write something: ");
                ui.text_edit_singleline(&mut self.label);
            });

            let mut alternatives: Vec<String> = match serialport::available_ports() {
                Ok(mut v) => v.iter_mut().map(|p| p.port_name.clone()).collect(),
                _ => {
                    vec!["No port Found".to_string()]
                }
            };
            if alternatives.is_empty() {
                alternatives.append(&mut vec!["No port found".to_string()]);
            }

            egui::ComboBox::from_label("Select serial port").show_index(
                ui,
                &mut self.selected_port,
                alternatives.len(),
                |i| alternatives[i].clone(),
            );
            if (!serialport::available_ports()
                .expect("Serial port error")
                .is_empty())
                && ui.button("Connect").clicked()
            {
                self.communicator
                    .connect(alternatives[self.selected_port].clone());
            }
            if ui.button("Disconnect").clicked() {
                self.communicator.stop();
            }
            ui.heading("Active: ".to_owned() + self.communicator.active_scenario());
            ui.add(egui::Slider::new(&mut self.temp, 0.0..=10.0).text("value"));

            ui.add(Gauge::new(self.temp, 0.0..=37.0, 200.0, Color32::RED).text("hello"));
            ui.separator();

            ui.add(egui::github_link_file!(
                "https://github.com/emilk/eframe_template/blob/master/",
                "Source code."
            ));

            ui.with_layout(egui::Layout::bottom_up(egui::Align::LEFT), |ui| {
                powered_by_egui_and_eframe(ui);
                egui::warn_if_debug_build(ui);
            });
        });
    }

    /// Called by the frame work to save state before shutdown.
    fn save(&mut self, storage: &mut dyn eframe::Storage) {
        eframe::set_value(storage, eframe::APP_KEY, self);
    }
}

fn powered_by_egui_and_eframe(ui: &mut egui::Ui) {
    ui.horizontal(|ui| {
        ui.spacing_mut().item_spacing.x = 0.0;
        ui.label("Powered by ");
        ui.hyperlink_to("egui", "https://github.com/emilk/egui");
        ui.label(" and ");
        ui.hyperlink_to(
            "eframe",
            "https://github.com/emilk/egui/tree/master/crates/eframe",
        );
        ui.label(".");
    });
}
