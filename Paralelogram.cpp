#include "Paralelogram.h"

Paralelogram::Paralelogram() {
}

Paralelogram::Paralelogram(float a_, float b_, float angle_) {
	a = a_;
	b = b_;
	angle = angle_;
}

float Paralelogram::get_field() const {
	return a * b * sin(angle);
}

std::string Paralelogram::to_string() const {
	std::stringstream ss;
	ss << "a: " << a << " b: " << b << " angle: " << angle << " field: " << get_field();
	return ss.str();
}

std::string Paralelogram::to_raw_data() {
	std::stringstream ss;
	ss << a << " " << b << " " << angle;
	return ss.str();
}

std::ostream& operator<< (std::ostream& o, const Paralelogram& obj) {
	return o << obj.to_string();
}

std::ostream& operator<< (std::ostream& o, const Paralelogram* obj) {
	return o << obj->to_string();
}