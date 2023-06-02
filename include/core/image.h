#ifndef NAIVE_BAYES_IMAGE_H
#define NAIVE_BAYES_IMAGE_H

#include <vector>

namespace naivebayes {
class Image {
 public:
  /**
   * Constructs a default image object with no default size or image pixel
   * values.
   */
  Image() = default;

  /**
   * Constructs image object for a parameterized image size.
   */
  Image(const size_t image_size);

  /**
   * Constructs image object from a parameterized 2d vector of image.
   */
  Image(const std::vector<std::vector<int>> &other_image);

  /**
   * Locates and return a int pixel value (0, 1) at specified row and and col
   * index.
   */
  int at(const size_t row, const size_t col) const;

  /**
   * Returns the current image object 2d image vector size.
   */
  size_t size() const;

  /**
   * Extracts 2d vector image from the file and updates image object to the
   * extracted image.
   */
  friend std::istream &operator>>(std::istream &input_stream, Image &image);

  /**
   * Inserts 2d vector image into the file from image object.
   */
  friend std::ostream &operator<<(std::ostream &output_stream, Image &image);

  /**
   * Compares two image object.
   * (Mostly used for testing purposes.)
   */
  bool operator==(const Image &other_image);

 private:
  std::vector<std::vector<int>> image_;
};
}  // namespace naivebayes

#endif  // NAIVE_BAYES_IMAGE_H
