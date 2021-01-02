use crate::vector::Vector;
use crate::vector::Point;

#[derive(Debug, Copy, Clone)]
pub struct Ray {
    pub orig: Point,
    pub dir: Vector,
}

impl Ray {
    pub fn at(self, t: f64) -> Point {
        self.orig + self.dir * t
    }
}
