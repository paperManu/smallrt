use crate::hittable::Hittable;
use crate::hittable::HitRecord;
use crate::ray::Ray;

pub struct HittableList {
    objects: Vec<Box<dyn Hittable>>,
}

impl Hittable for HittableList {
    fn hit(&self, ray: &Ray, t_min: f64, t_max: f64) -> Result<HitRecord, bool> {
        let mut closest_so_far: f64 = t_max;
        let mut record: Result<HitRecord, bool> = Err(false);

        for object in &self.objects {
            let result = object.hit(ray, t_min, closest_so_far);
            record = match result {
                Ok(record) => {
                    closest_so_far = record.t;
                    Ok(record)
                },
                Err(..) => continue
            };
        }

        return record;
    }
}

impl HittableList {
    pub fn add_object(&mut self, object: Box<dyn Hittable>) {
        self.objects.push(object);
    }

    pub fn clear(&mut self) {
        self.objects.clear();
    }

    pub fn new() -> HittableList {
        HittableList {
            objects: Vec::new()
        }
    }
}
