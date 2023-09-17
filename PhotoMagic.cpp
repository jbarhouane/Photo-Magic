#include <iostream>
#include <string>
#include <cmath>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "FibLFSR.hpp"

using namespace std;
using namespace sf;

void transform(Image& image, FibLFSR* seed);

string dec_to_bin(int decimal);

int bin_to_dec(string binary);

int main(int argc, char* argv[]) {
	string in_file = argv[1];
	string out_file = argv[2];
	string binary = argv[3];
	FibLFSR a(binary);
	Image image;
	if(!image.loadFromFile(in_file)) {
		return -1;
	}
	transform(image, &a);
	return 0;
}

void transform(Image& image, FibLFSR* seed) {
	Image original_image = image;
	unsigned int x, y;
	int n;
	n = rand() % 16;
	seed->generate(n);
	int r_code = bin_to_dec(seed->get_seed()) % 255;
	n = rand() % 16;
	seed->generate(n);
	int g_code = bin_to_dec(seed->get_seed()) % 255;
	n = rand() % 16;
	seed->generate(n);
	int b_code = bin_to_dec(seed->get_seed()) % 255;
	Color p;
	Vector2u size = image.getSize();

	for (x = 0; x < size.x; x++) {
		for (y = 0; y < size.y; y++) {
			p = image.getPixel(x, y);
			p.r = p.r ^ r_code;
			p.g = p.g ^ g_code;
			p.b = p.b ^ b_code;
			image.setPixel(x, y, p);
		}
	}
	RenderWindow window1(VideoMode(size.x, size.y), "Encrypted Image");

	Texture texture;
	texture.loadFromImage(image);

	Sprite sprite;
	sprite.setTexture(texture);

	RenderWindow window2(VideoMode(size.x, size.y), "Original Image");

	Texture texture2;
	texture2.loadFromImage(original_image);

	Sprite sprite2;
	sprite2.setTexture(texture2);

	while (window1.isOpen() && window2.isOpen()) {
		Event event;
		while (window1.pollEvent(event)) {
			if (event.type == Event::Closed)
				window1.close();
		}
		while (window2.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window2.close();
		}
		window1.clear();
		window1.draw(sprite);
		window1.display();
		window2.clear();
		window2.draw(sprite2);
		window2.display();
	}
	if (!image.saveToFile("output_file.png"))
	{
		throw exception();
	}

}

string dec_to_bin(int decimal) {
	string binary = "";
	string temp = "";
	int b_length = 0;
	int i = 0;
	while (decimal > 0)
	{
		binary += to_string(decimal % 2);
		decimal /= 2;
	}
	if (binary.length() != 16)
	{
		b_length = 16 - binary.length();
		temp += binary;
		binary = "";
		for (i = 0; i < b_length; i++)
		{
			binary += '0';
		}
		binary += temp;
	}
	return binary;
}

int bin_to_dec(string binary) {
	int decimal = 0;
	int b_length = binary.length();
	int i = 0;
	for (i = 0; i < b_length; i++)
	{
		decimal += (binary.at(i) % 2) * pow(2, b_length - i - 1);
	}

	return decimal;
}
