use crate::vector::Color;

pub fn write_color(color: &Color) {
    println!("{} {} {}\n", 255.999 * color.x, 255.999 * color.y, 255.999 * color.z);
}
