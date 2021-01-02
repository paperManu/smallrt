mod ray;
mod utils;
mod vector;

use utils::write_color;
use vector::Color;

fn main() {
    let image_width = 256;
    let image_height = 256;

    println!("P3\n{} {}\n255\n", image_width, image_height);

    for y in (0..image_height).rev() {
        for x in 0..image_width {
            let color = Color {
                x: (x as f64) / ((image_width as f64) - 1.0),
                y: (y as f64) / ((image_height as f64) - 1.0),
                z: 0.25
            };
            write_color(&color);
        }
    }
}
