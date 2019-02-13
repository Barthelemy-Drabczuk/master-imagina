#ifndef IMAGE_BASE_H
#define IMAGE_BASE_H

#include <iostream>
#include <fstream>
#include <vector>

//#include "image_pgm_ppm.h"

typedef unsigned char OCTET;

class ImageBase {

public:

	ImageBase();
	ImageBase(size_t width, size_t height);
	ImageBase(const std::string& filename);

	size_t height() const;
	size_t width() const;
	size_t size() const;

	bool valid() const;
	bool on_bounds(size_t raw, size_t column) const;
	bool same_resolution(const ImageBase& image) const;

	void load(const std::string& filename);
	void save(const std::string& filename);

	friend std::istream& operator>>(std::istream& is, ImageBase& image);
	friend std::ostream& operator<<(std::ostream& os, const ImageBase& image);

protected:

	size_t m_height;
	size_t m_width;
	bool m_valid;

	// charge une image en fonction de sont type (.ppm / .pgm)
	virtual void read(std::istream& is) = 0;
	virtual void write(std::ostream& os) const = 0;
};

////////////////////////////////// ImagePGM ////////////////////////////////////////

class ImagePGM : public ImageBase {

public:

	typedef OCTET* iterator;
    typedef const OCTET* const_iterator;

	ImagePGM();
	ImagePGM(size_t width, size_t height);
	ImagePGM(const std::string& filename);

	void resize(size_t width, size_t height);

	// Access data in array style pgm(n)
	OCTET& operator[](size_t n);
	const OCTET& operator[](size_t n) const;

	// Access data in matrix style pgm(i, j)
	OCTET& operator()(size_t raw, size_t column);
	const OCTET& operator()(size_t raw, size_t column) const;

	// Accessor of internal data
	OCTET* data();
	const OCTET* data() const;

	iterator begin();
	const_iterator begin() const;

	iterator end();
	const_iterator end() const;

protected:

	std::vector<OCTET> m_data;

	void read(std::istream& is);
	void write(std::ostream& os) const;
};

////////////////////////////////// ImagePPM ////////////////////////////////////////

class ImagePPM : public ImageBase {

public:	

	ImagePPM();
	ImagePPM(size_t width, size_t height);
	ImagePPM(const std::string& filename);
	ImagePPM(const ImagePGM& red, const ImagePGM& green, const ImagePGM& blue);

	OCTET& red(size_t raw, size_t column);
	const OCTET& red(size_t raw, size_t column) const;

	OCTET& green(size_t raw, size_t column);
	const OCTET& green(size_t raw, size_t column) const;

	OCTET& blue(size_t raw, size_t column);
	const OCTET& blue(size_t raw, size_t column) const;

	// Getters/Setters pour checker que les resolutions des parties R/G/B de l'image sont les m�mes.

	const ImagePGM& red() const;
	const ImagePGM& green() const;
	const ImagePGM& blue() const;

	void red(const ImagePGM& red);
	void green(const ImagePGM& green);
	void blue(const ImagePGM& blue);

protected:

	ImagePGM m_red;
	ImagePGM m_green;
	ImagePGM m_blue;

	void read(std::istream& is);
	void write(std::ostream& os) const;
};

#endif