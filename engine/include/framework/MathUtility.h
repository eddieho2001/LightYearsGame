#pragma once
#include <SFML/Graphics.hpp>


namespace ly {

	static const float epsilon{ 0.0000001f };

	sf::Vector2f Rotation2Vecor(float rotation);
	float Degree2Radian(float degree);
	float Radian2Degree(float rad);

	//Calculate vector length
	template<typename T>
	float Calculate2DVectorLength(const sf::Vector2<T>& vector) {
		return std::sqrt( (vector.x * vector.x) + (vector.y * vector.y));
	};

	//mutliple scalar with vector
	template<typename T>
	sf::Vector2<T>& Scale2DVector(sf::Vector2<T>& vec, float amount) {
		vec.x *= amount;
		vec.y *= amount;
		return vec;
	}

	//Normalize the vector
	template<typename T>
	sf::Vector2<T>& Normalize(sf::Vector2<T>& vec) {
		float vecLen = Calculate2DVectorLength<T>(vec);
		if (std::fabs(vecLen) < epsilon) return vec;

		return Scale2DVector(vec, 1.f/vecLen);
	}

}