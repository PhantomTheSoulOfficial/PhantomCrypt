#include <iostream>
#include <vector>
#include <functional>
#include <cstddef>
#include <stdexcept>
#include <algorithm>

class Pixel {
private:
	uint8_t r, g, b, a;
	
public:
	bool isTransparent() const { return a == 0; }
	bool isSemiTransparent() const { return a > 0 && a < 255; }
	bool isOpaque() const { return a == 255; }

	Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) : r(red), g(green), b(blue), a(alpha) {}
	Pixel() : r(0), g(0), b(0), a(255) {}

	void setRed(uint8_t red) { r = red; }
	void setGreen(uint8_t green) { g = green; }
	void setBlue(uint8_t blue) { b = blue; }
	void setAlpha(uint8_t alpha) { a = alpha; }

	uint8_t getRed() const { return r; }
	uint8_t getGreen() const { return g; }
	uint8_t getBlue() const { return b; }
	uint8_t getAlpha() const { return a; }

	void print() const {
		std::cout << "Pixel(R: " << static_cast<int>(r) << ", G: " << static_cast<int>(g)
			<< ", B: " << static_cast<int>(b) << ", A: " << static_cast<int>(a) << ")\n";
	}

	bool operator==(const Pixel& other) const {
		return r == other.r && g == other.g && b == other.b && a == other.a;
	}

	bool operator!=(const Pixel& other) const {
		return !(*this == other);
	}
};

template <typename T>
class Matrix {
private:
	std::size_t width, height;
	std::vector<T> data;

	bool isValidIndex(std::size_t x, std::size_t y) const {
		return x < width && y < height;
	}

	void checkIndex(std::size_t x, std::size_t y) const {
		if (!isValidIndex(x, y)) {
			throw std::out_of_range("Matrix index out of range");
		}
	}

public:
	Matrix(std::size_t w, std::size_t h) : width(w), height(h), data(w* h) {
		if (w == 0 || h == 0) {
			throw std::invalid_argument("Matrix dimensions must be greater than zero");
		}
	}

	void set(std::size_t x, std::size_t y, const T& value) {
		checkIndex(x, y);
		data[y * width + x] = value;
	}

	T& get (std::size_t x, std::size_t y) {
		checkIndex(x, y);
		return data[y * width + x];
	}

	const T& get(std::size_t x, std::size_t y) const {
		checkIndex(x, y);
		return data[y * width + x];
	}

	std::size_t getWidth() const { return width; }
	std::size_t getHeight() const { return height; }

	void fill(const T& value) {
		std::fill(data.begin(), data.end(), value);
	}

	void reset() {
		data.clear();
		data.resize(width * height);
	}

};

class Image {
	private:
		Matrix<Pixel> pixels;
	
public:
	Image(std::size_t width, std::size_t height) : pixels(width, height) {}
	void setPixel(std::size_t x, std::size_t y, const Pixel& pixel) {
		pixels.set(x, y, pixel);
	}

	std::size_t getWidth() const { return pixels.getWidth(); }
	std::size_t getHeight() const { return pixels.getHeight(); }

	Pixel& getPixel(std::size_t x, std::size_t y) {
		return pixels.get(x, y);
	}

	const Pixel& getPixel(std::size_t x, std::size_t y) const {
		return pixels.get(x, y);
	}

	void print() const {
		for (std::size_t y = 0; y < getHeight(); ++y) {
			for (std::size_t x = 0; x < getWidth(); ++x) {
				getPixel(x, y).print();
			}
		}
	}

	void fill(const Pixel& pixel) {
		pixels.fill(pixel);
	}

	void reset() {
		pixels.reset();
	}

	void forEachPixel(const std::function<void(Pixel&, std::size_t, std::size_t)>& func) {
		for (std::size_t y = 0; y < getHeight(); ++y) {
			for (std::size_t x = 0; x < getWidth(); ++x) {
				func(getPixel(x, y), x, y);
			}
		}
	}
};

class PhantomCrypt {
public:
	void invert(Image& image) {
		image.forEachPixel([](Pixel& pixel, std::size_t x, std::size_t y) {
			pixel.setRed(255 - pixel.getRed());
			pixel.setGreen(255 - pixel.getGreen());
			pixel.setBlue(255 - pixel.getBlue());
			});
	}
};

int main() {
	Image img(3, 3);

	img.forEachPixel([](Pixel& pixel, std::size_t x, std::size_t y) {
		pixel.setRed(static_cast<uint8_t>(x * 85));
		pixel.setGreen(static_cast<uint8_t>(y * 85));
		pixel.setBlue(128);
		pixel.setAlpha(255);
		});

	img.print();

	PhantomCrypt crypt;
	crypt.invert(img);

	img.print();

	return 0;
}