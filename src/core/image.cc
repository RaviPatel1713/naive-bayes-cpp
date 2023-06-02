#include "core/image.h"

#include <iostream>
#include <vector>

namespace naivebayes {
Image::Image(const size_t image_size) {
  image_ = std::vector<std::vector<int>>(28, std::vector<int>(28, 0));
}

size_t kImageSize = 28;

int Image::at(const size_t row, const size_t col)const {
  return image_.at(row).at(col);
}

size_t Image::size() const {
  return image_.size();
}

std::istream &operator>>(std::istream &input_stream, Image &image) {
  std::vector<std::vector<int>> featured_image(kImageSize,
                                               std::vector<int>(kImageSize, 0));
  for (size_t row = 0; row < kImageSize; ++row) {
    std::string current_row;
    std::getline(input_stream, current_row);
    if (current_row.empty()) continue;

    for (size_t col = 0; col < kImageSize; ++col) {
      if (current_row.at(col) == '#' || current_row.at(col) == '+') {
        featured_image[row][col] = 1;
      }
    }
  }
  image.image_ = featured_image; // usage of overloaded operator= to set Image class
                          // object to feature image(2d vector of int)
  return input_stream;
}

std::ostream &operator<<(std::ostream &output_stream, Image &image) {
  for(size_t r = 0; r < image.size(); ++r){
    for(size_t c = 0; c < image.size(); ++c){
      output_stream << image.at(r, c);
    }
    output_stream << "\n";
  }
  return output_stream;
}
Image::Image(const std::vector<std::vector<int>> &other_image) {
  image_ = other_image;
}
bool Image::operator==(const Image &other_image) {
  if (image_.size() != other_image.size()) return false;
  for (size_t row = 0; row < image_.size(); ++row){
    for (size_t col = 0; col < image_.size(); ++col) {
      if (image_.at(row).at(col) != other_image.at(row, col)){
        return false;
      }
    }
  }
  return true;
}

}  // namespace naivebayes