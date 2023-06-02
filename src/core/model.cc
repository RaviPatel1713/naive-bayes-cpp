#include "core/model.h"

#include "core/image_and_label_dataset.h"
#include <iostream>

namespace naivebayes {
Model::Model(const std::string& image_file, const std::string& image_label_file)
    : Model(image_file, image_label_file, 1.0) {
}

Model::Model(const std::string& image_file, const std::string& image_label_file,
             const double kLaPlace) {
  ImageAndLabelDataset training_data =
      ImageAndLabelDataset(image_file, image_label_file, kLaPlace);

  image_size_ = training_data.GetImageSize();
  class_prior_probabilities_ = training_data.GenerateClassPriorProbabilities();
  feature_probability_matrix_ =
      training_data.GenerateFeatureProbabilityMatrix();


}

Model::Model(const std::vector<double> &class_prior_probabilities,
             const std::vector<std::vector<std::vector<double>>>
             &feature_probability_matrix)
    : class_prior_probabilities_(class_prior_probabilities),
      feature_probability_matrix_(feature_probability_matrix) {
}

std::istream& operator>>(std::istream& input_stream, Model& model) {
  std::vector<double> class_prior_probabilities;
  std::vector<std::vector<std::vector<double>>> feature_probability_matrix;
  size_t image_size;

  input_stream >> image_size;

  for (size_t c = 0; c < 10; ++c) {
    double prob;
    input_stream >> prob;
    class_prior_probabilities.push_back(prob);
  }

  for (size_t c = 0; c < 10; ++c) {
    std::vector<std::vector<double>> image_rows;
    for (size_t row = 0; row < 28; ++row) {
      std::vector<double> row_prob;
      for (size_t col = 0; col < 28; ++col) {
        double prob;
        input_stream >> prob;
        row_prob.push_back(prob);
      }
      image_rows.push_back(row_prob);
    }
    feature_probability_matrix.push_back(image_rows);
  }
  model.image_size_ = image_size;
  model.class_prior_probabilities_ = class_prior_probabilities;
  model.feature_probability_matrix_ = feature_probability_matrix;
  return input_stream;
}

std::ostream& operator<<(std::ostream& output_stream, Model& model) {
  std::vector<double> class_prior_probabilities =
      model.GetClassPriorProbabilities();
  std::vector<std::vector<std::vector<double>>> feature_probability_matrix =
      model.GetFeatureProbabilityMatrix();

  output_stream << model.GetImageSize();
  output_stream << "\n";

  for (size_t c = 0; c < class_prior_probabilities.size(); ++c) {
    output_stream << class_prior_probabilities[c];
    if (c < class_prior_probabilities.size() - 1)
      output_stream << " ";
  }
  output_stream << "\n";

  for (size_t c = 0; c < class_prior_probabilities.size(); ++c) {
    for (size_t row = 0; row < 28; ++row) {
      for (size_t col = 0; col < 28; ++col) {
        output_stream << feature_probability_matrix[c][row][col];
        if (col < 27)
          output_stream << " ";
      }
      output_stream << "\n";
    }
  }
  return output_stream;
}

std::vector<double> Model::GetClassPriorProbabilities() {
  return class_prior_probabilities_;
}

std::vector<std::vector<std::vector<double>>>
Model::GetFeatureProbabilityMatrix() {
  return feature_probability_matrix_;
}

void Model::SetModelTo(const std::vector<double>& class_prior_probabilities,
                       const std::vector<std::vector<std::vector<double>>>&
                           feature_probability_matrix) {
  class_prior_probabilities_ = class_prior_probabilities;
  feature_probability_matrix_ = feature_probability_matrix;
}

size_t Model::GetImageSize() {
  return image_size_;
}

void Model::SetImageSize(size_t size) {
  image_size_ = size;
}
}  // namespace naivebayes