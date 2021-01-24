mod ray;
mod sphere;
mod utils;
mod vector;
mod hittable;
mod hittable_list;
mod rtweekend;

use hittable::Hittable;
use hittable_list::HittableList;
use ray::Ray;
use rtweekend::INFINITY;
use sphere::Sphere;
use utils::write_color;
use vector::Color;
use vector::Point;
use vector::Vector;

fn hit_sphere(center: &Point, radius: f64, ray: &Ray) -> f64 {
    let oc = ray.orig - center;
    let a = ray.dir.length_squared();
    let half_b = oc.dot(&ray.dir);
    let c = oc.length_squared() - radius * radius;
    let discriminant = half_b * half_b - a * c;
    if discriminant < 0.0 {
        return -1.0;
    }
    else {
        return (-half_b - discriminant.sqrt()) / a;
    }
}

fn ray_color(ray: &Ray, world: &dyn Hittable) -> Color {
    let hit_record = world.hit(ray, 0.0, INFINITY);
    match hit_record {
        Ok(record) => {
            return 0.5 * (record.normal + Color { x: 1.0, y: 1.0, z: 1.0 });
        }
        Err(..) => {}
    }

    let unit_direction = ray.dir.unit();
    let t = 0.5 * (unit_direction.y + 1.0);
    let white = Color { x: 1.0, y: 1.0, z: 1.0 };
    let blueish = Color { x: 0.5, y: 0.7, z: 1.0 };

    (1.0 - t) * white + t * blueish
}

fn main() {
    // Image
    let aspect_ratio: f64 = 16.0 / 9.0;
    let image_width: u64 = 400;
    let image_height: u64 = ((image_width as f64) / aspect_ratio) as u64;

    // World
    let mut world = HittableList::new();
    world.add_object(Box::new(Sphere { 
            center: Point { x: 0.0, y: 0.0, z: -1.0},
            radius: 0.5
    }));
    world.add_object(Box::new(Sphere { 
            center: Point { x: 0.0, y: -100.5, z: -1.0},
            radius: 100.0
    }));

    // Camera
    let viewport_height: f64 = 2.0;
    let viewport_width: f64 = aspect_ratio * viewport_height;
    let focal_length: f64 = 1.0;

    let origin = Point { x: 0.0, y: 0.0, z: 0.0 };
    let horizontal = Vector { x: viewport_width, y: 0.0, z: 0.0 };
    let vertical = Vector { x: 0.0, y: viewport_height, z: 0.0 };
    let focal_vector = Vector { x: 0.0, y: 0.0, z: focal_length };

    let lower_left_corner = origin - &horizontal / 2.0 - &vertical / 2.0 - focal_vector;

    println!("P3\n{} {}\n255\n", image_width, image_height);

    for y in (0..image_height).rev() {
        for x in 0..image_width {
            let u = (x as f64) / ((image_width - 1) as f64);
            let v = (y as f64) / ((image_height - 1) as f64);
            let ray = Ray {
                orig: origin,
                dir: &lower_left_corner + &horizontal * u + &vertical * v - origin
            };
            let pixel_color = ray_color(&ray, &world);
            write_color(&pixel_color);
        }
    }
}
