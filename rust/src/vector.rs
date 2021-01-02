use std::ops;
use std::string::String;

#[derive(Debug, Copy, Clone)]
pub struct Vector {
    pub x: f64,
    pub y: f64,
    pub z: f64
}

pub type Point = Vector;
pub type Color = Vector;

impl ops::Neg for &Vector {
    type Output = Vector;

    fn neg(self) -> Vector {
        Vector {
            x: -self.x,
            y: -self.y,
            z: -self.z
        }
    }
}

impl ops::Add<&Vector> for &Vector {
    type Output = Vector;

    fn add(self, rhs: &Vector) -> Vector {
        Vector {
            x: self.x + rhs.x,
            y: self.y + rhs.y,
            z: self.z + rhs.z
        }
    }
}

impl ops::Mul<f64> for &Vector {
    type Output = Vector;

    fn mul(self, rhs: f64) -> Vector {
        Vector {
            x: self.x * rhs,
            y: self.y * rhs,
            z: self.z * rhs
        }
    }
}

impl ops::Mul<&Vector> for f64 {
    type Output = Vector;

    fn mul(self, rhs: &Vector) -> Vector{
        rhs * self
    }
}

impl ops::Mul<&Vector> for &Vector {
    type Output = Vector;

    fn mul(self, rhs: &Vector) -> Vector {
        Vector {
            x: self.x * rhs.x,
            y: self.y * rhs.y,
            z: self.z * rhs.z
        }
    }
}

impl ops::Div<f64> for &Vector {
    type Output = Vector;

    fn div(self, rhs: f64) -> Vector {
        self * (1.0 / rhs)
    }
}

impl ToString for &Vector {
    fn to_string(&self) -> String {
        self.x.to_string() + " " + &self.y.to_string() + " " + &self.z.to_string()
    }
}

impl Vector {
    pub fn dot(&self, rhs: &Vector) -> Vector {
        Vector {
            x: self.y * rhs.z - self.z * rhs.y,
            y: self.z * rhs.x - self.x * rhs.z,
            z: self.x * rhs.y - self.y * rhs.x
        }
    }

    pub fn length_squared(&self) -> f64 {
        self.x * self.x + self.y * self.y + self.z * self.z
    }

    pub fn length(&self) -> f64 {
        self.length_squared().sqrt()
    }

    pub fn unit(&self) -> Vector {
        let length = self.length();
        self / length
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn neg() {
        let vector = Vector {
            x: 1.0,
            y: 1.0,
            z: 1.0
        };

        let neg_vector = -&vector;

        assert!(neg_vector.x == -vector.x);
    }

    #[test]
    fn add() {
        let vec1 = Vector {
            x: 1.0,
            y: 1.0,
            z: 1.0
        };

        let vec2 = Vector {
            x: 2.0,
            y: 3.0,
            z: 4.0
        };

        let vec3 = &vec1 + &vec2;

        assert!(vec3.x == 3.0);
        assert!(vec3.y == 4.0);
        assert!(vec3.z == 5.0);
    }

    #[test]
    fn mul() {
        let vec1 = Vector {
            x: 1.0,
            y: 1.0,
            z: 1.0
        };

        let vec2 = &vec1 * 2.0;

        assert!(vec2.x == 2.0);
        assert!(vec2.y == 2.0);
        assert!(vec2.z == 2.0);
    }
}
