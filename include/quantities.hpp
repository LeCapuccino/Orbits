#include <iostream>
#include <cmath>

#ifndef QUANTITIES_HPP
#define QUANTITIES_HPP

namespace quantities {
	class Scalar {
	public:
		double magnitude;

		Scalar() {}

		Scalar(double value) {
			magnitude = value;
		}

		void view() {
			std::cout << magnitude << "\n";
		}

		Scalar operator!() {
			if (magnitude >= 0) {
				return Scalar(magnitude);
			}
			else {
				return Scalar(-magnitude);
			}
		}

		Scalar operator+() {
			return Scalar(magnitude);
		}

		Scalar operator-() {
			return Scalar(-magnitude);
		}

		Scalar operator+(Scalar other) {
			return Scalar(magnitude + other.magnitude);
		}

		Scalar operator-(Scalar other) {
			return Scalar(magnitude - other.magnitude);
		}

		Scalar operator*(Scalar other) {
			return Scalar(magnitude * other.magnitude);
		}

		Scalar operator/(Scalar other) {
			return Scalar(magnitude / other.magnitude);
		}

		Scalar operator+=(Scalar other) {
			*this = *this + other;
			return *this;
		}

		Scalar operator-=(Scalar other) {
			*this = *this - other;
			return *this;
		}

		Scalar operator*=(Scalar other) {
			*this = *this * other;
			return *this;
		}

		Scalar operator/=(Scalar other) {
			*this = *this / other;
			return *this;
		}

		bool operator==(Scalar other) {
			return magnitude == other.magnitude;
		}
		
		bool operator!=(Scalar other) {
			return magnitude != other.magnitude;
		}

		bool operator>(Scalar other) {
			return magnitude > other.magnitude;
		}

		bool operator<(Scalar other) {
			return magnitude < other.magnitude;
		}

		bool operator>=(Scalar other) {
			return magnitude >= other.magnitude;
		}

		bool operator<=(Scalar other) {
			return magnitude <= other.magnitude;
		}

		Scalar operator^(int num) {
			return Scalar(std::pow(magnitude, num));
		}
	};

	class Vector {
	public:
		double coord[3];

		Vector() {}

		Vector(double x, double y, double z) {
			coord[0] = x;
			coord[1] = y;
			coord[2] = z;
		}

		void view() {
			std::cout << "(" << coord[0] << ", " << coord[1] << ", "<< coord[2] << ")\n";
		}

		Scalar operator!() {
			return Scalar(std::sqrt(coord[0]*coord[0] + 
									coord[1]*coord[1] + 
									coord[2]*coord[2]));
		}

		Vector operator+() {
			return Vector(coord[0], coord[1], coord[2]);
		}

		Vector operator-() {
			return Vector(-coord[0], -coord[1], -coord[2]);
		}

		Vector operator*(Scalar other) {
			return Vector(coord[0] * other.magnitude, 
						  coord[1] * other.magnitude, 
						  coord[2] * other.magnitude);
		}

		Vector operator/(Scalar other) {
			return Vector(coord[0] / other.magnitude, 
						  coord[1] / other.magnitude, 
						  coord[2] / other.magnitude);
		}

		Vector operator+(Vector other) {
			return Vector(coord[0] + other.coord[0],
						  coord[1] + other.coord[1],
						  coord[2] + other.coord[2]);
		}

		Vector operator-(Vector other) {
			return Vector(coord[0] - other.coord[0],
						  coord[1] - other.coord[1],
						  coord[2] - other.coord[2]);
		}

		Vector operator+=(Vector other) {
			*this = *this + other;
			return *this;
		}

		Vector operator-=(Vector other) {
			*this = *this - other;
			return *this;
		}

		Vector operator*=(Scalar other) {
			*this = *this * other;
			return *this;
		}

		Vector operator/=(Scalar other) {
			*this = *this / other;
			return *this;
		}

		Scalar operator||(Vector other) {
			return Scalar(coord[0]*other.coord[0] +
						  coord[1]*other.coord[1] +
				   		  coord[2]*other.coord[2]);
		}

		Vector operator&&(Vector other) {
			return Vector(coord[1]*other.coord[2] - coord[2]*other.coord[1],
						  coord[2]*other.coord[0] - coord[0]*other.coord[2],
				   		  coord[0]*other.coord[1] - coord[1]*other.coord[0]);
		}
	};
}

#endif