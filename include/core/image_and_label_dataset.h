#ifndef NAIVE_BAYES_IMAGE_AND_LABEL_DATASET_H
#define NAIVE_BAYES_IMAGE_AND_LABEL_DATASET_H

#include <fstream>
#include <map>
#include <string>
#include "core/image.h"

namespace naivebayes {
class ImageAndLabelDataset {
 public:
  /**
   * Constructs training-data object for ImageAndLabelDataset with
   * a default kLaPlace smoothing factor of 1.
   */
  ImageAndLabelDataset(const std::string &image_file,
                       const std::string &image_label_file);

  /**
   * Constructs training-data object for ImageAndLabelDataset with
   * a parameterized kLaPlace smoothing factor.
   */
  ImageAndLabelDataset(const std::string &image_file,
                       const std::string &image_label_file,
                       const double k_laplace);

  /**
   * Returns current dataset size - total number image of training image.
   */
  size_t GetDatasetSize() const;

  /**
   * Generates a vector of class prior probabilities with training data
   * and return the vector of class prior probabilities.
   */
  std::vector<double> GenerateClassPriorProbabilities() const;

  /**
   * Generates a 3d vector of all classes feature probability and returns
   * the 3d vector.
   */
  std::vector<std::vector<std::vector<double>>>
  GenerateFeatureProbabilityMatrix() const;

  /**
   * Returns the image size of current training dataset.
   */
  size_t GetImageSize() const;

 private:
  std::vector<std::vector<Image>> label_and_image_dataset_;
  bool error;
  const double kLaPlace;
};

}  // namespace naivebayes


#endif  // NAIVE_BAYES_IMAGE_AND_LABEL_DATASET_H
