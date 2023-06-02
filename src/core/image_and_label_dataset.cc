#include <core/image_and_label_dataset.h>

#include <vector>

namespace naivebayes {

ImageAndLabelDataset::ImageAndLabelDataset(const std::string &image_file,
                                           const std::string &image_label_file)
    : ImageAndLabelDataset(image_file, image_label_file, 1) {}

ImageAndLabelDataset::ImageAndLabelDataset(const std::string &image_file,
                                           const std::string &image_label_file,
                                           const double k_laplace) : kLaPlace(k_laplace){

  for (size_t c = 0; c < 10; ++c) label_and_image_dataset_.emplace_back();

  error = true;
  if (image_file.empty() || image_label_file.empty())
    error = false;

  std::ifstream image_file_reader;
  image_file_reader.open(image_file);

  std::ifstream image_label_file_reader;
  image_label_file_reader.open(image_label_file);

  if (!image_label_file_reader || !image_file_reader)
    error = false;

  while (!image_file_reader.eof() && !image_label_file_reader.eof()) {
    Image training_image;
    size_t label;
    image_file_reader >> training_image;
    image_label_file_reader >> label;
    label_and_image_dataset_[label].push_back(training_image);
  }
  image_label_file_reader.close();
  image_file_reader.close();

}

std::vector<double> ImageAndLabelDataset::GenerateClassPriorProbabilities() const{
  std::vector<double> class_prior_probabilities;

  for (size_t class_type = 0; class_type < label_and_image_dataset_.size();
       ++class_type) {
    double numer = label_and_image_dataset_.at(class_type).size() + kLaPlace;
    double denom = GetDatasetSize() + kLaPlace * 10;
    class_prior_probabilities.push_back(static_cast<double>(numer / denom));
  }
  return class_prior_probabilities;
}

std::vector<std::vector<std::vector<double>>>
ImageAndLabelDataset::GenerateFeatureProbabilityMatrix() const {
  size_t class_size = label_and_image_dataset_.size();
  size_t image_size = label_and_image_dataset_[0][0].size();

  std::vector<std::vector<std::vector<double>>> matrix(
      class_size, std::vector<std::vector<double>>(
          image_size, std::vector<double>(image_size)));

  double feature_count;
  for (size_t c = 0; c < class_size; ++c) {
    for (size_t row = 0; row < image_size; ++row) {
      for (size_t col = 0; col < image_size; ++col) {
        size_t image_objects = label_and_image_dataset_.at(c).size();
        feature_count = 0;
        for (size_t i = 0; i < image_objects; ++i) {
          feature_count = feature_count + label_and_image_dataset_.at(c).at(i).at(row, col);
        }
        double prob = (feature_count + kLaPlace)/(image_objects + kLaPlace * 2.0);
        matrix[c][row][col] = prob;
      }
    }
  }

  return matrix;
}
size_t ImageAndLabelDataset::GetDatasetSize() const{
  size_t size = 0;
  for (size_t c = 0; c < label_and_image_dataset_.size(); ++c) {
    size = size + label_and_image_dataset_.at(c).size();
  }
  return size;
}
size_t ImageAndLabelDataset::GetImageSize() const {
  if (label_and_image_dataset_.size() == 0){
    return 0;
  }
  return label_and_image_dataset_.at(0).at(0).size();
}
}  // namespace naivebayes
