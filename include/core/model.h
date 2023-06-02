#ifndef NAIVE_BAYES_MODEL_H
#define NAIVE_BAYES_MODEL_H

#include <iostream>
#include <string>
#include <vector>
#include "core/image_and_label_dataset.h"

namespace naivebayes {
class Model {
 public:
  Model() = default;

  /**
   * Constructs a model from image and label file path with deefault kLaPlace
   * smoothing of 1.
   */
  Model(const std::string &image_file, const std::string &image_label_file);

  /**
   * Constructs a model from image, label file path and a specified kLaPlace
   * smoothing factor.
   */
  Model(const std::string &image_file, const std::string &image_label_file,
        const double k_laplace);

  /**
   * Constructs a model from parameterized class prior and feature matrix
   * probabilities.
   */
  Model(const std::vector<double> &class_prior_probabilities,
        const std::vector<std::vector<std::vector<double>>>
            &feature_probability_matrix);

  // getter methods
  std::vector<double> GetClassPriorProbabilities();
  std::vector<std::vector<std::vector<double>>> GetFeatureProbabilityMatrix();
  void SetModelTo(const std::vector<double> &class_prior_probabilities,
                  const std::vector<std::vector<std::vector<double>>>
                      &feature_probability_matrix);
  size_t GetImageSize();

  /**
   * Extracts trained model data from a file and loads into model class object.
   */
  friend std::istream &operator>>(std::istream &input_stream, Model &model);

  /**
   * Inserts trained model data into a file from model class object.
   */
  friend std::ostream &operator<<(std::ostream &output_stream, Model &model);

 private:
  std::vector<double> class_prior_probabilities_;
  std::vector<std::vector<std::vector<double>>> feature_probability_matrix_;
  size_t image_size_;
};
}  // namespace naivebayes


#endif  // NAIVE_BAYES_MODEL_H
