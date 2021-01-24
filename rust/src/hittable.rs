use crate::ray::Ray;
use crate::vector::Point;
use crate::vector::Vector;

#[derive(Debug, Copy, Clone)]
pub struct HitRecord {
    pub point: Point,
    pub normal: Vector,
    pub t: f64,
    pub front_face: bool,
}

impl HitRecord {
    pub fn set_face_normal(&mut self, ray: &Ray, outward_normal: Vector) {
        self.front_face = ray.dir.dot(&outward_normal) < 0.0;
        if self.front_face {
            self.normal = outward_normal;
        } else {
            self.normal = -outward_normal;
        }
    }
}

pub trait Hittable {
    fn hit(&self, ray: &Ray, t_min: f64, t_max: f64) -> Result<HitRecord, bool>;
}
