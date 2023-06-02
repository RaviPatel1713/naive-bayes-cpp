#ifndef NAIVE_BAYES_NAIVE_BAYES_CLASSIFIER_H
#define NAIVE_BAYES_NAIVE_BAYES_CLASSIFIER_H

#include <iostream>

#include "core/model.h"
#include "core/image.h"
namespace naivebayes {
class NaiveBayesClassifier {
 public:
  NaiveBayesClassifier() = default;

  /**
   * Constructs a classifier with a trained model and a default kLaPlace
   * smoothing of 1, and saves the model into a saving file specified.
   */
  NaiveBayesClassifier(const std::string &image_file,
                       const std::string &image_label_file,
                       const std::string &model_to_save_file);

  /**
   * Constructs a classifier with a trained model and a parameterized kLaPlace
   * smoothing, and saves the model into a saving file specified.
   */
  NaiveBayesClassifier(const std::string &image_file,
                       const std::string &image_label_file,
                       const std::string &model_to_save_file,
                       const double k_laplace);

  /**
   * * Constructs a classifier with a trained model and a default kLaPlace
   * smoothing of 1, and saves the model into a default model-saving file.
   */
  NaiveBayesClassifier(const std::string &image_file,
                       const std::string &image_label_file);

  /**
   * Constructs a classifier with a trained model and a parameterized kLaPlace
   * smoothing, and saves the model into a default model-saving file.
   */
  NaiveBayesClassifier(const std::string &image_file,
                       const std::string &image_label_file,
                       const double k_laplace);

  /**
   * Constructs a classifier and loads a trained model from a file.
   */
  NaiveBayesClassifier(const std::string &saved_model_file);

  /**
   * Classifies an image, passed in any of the follwing forms
   * - image object, 2d image vector, or an image file -
   * from a trained model.
   */
  size_t PerformClassification(Image &image_to_be_classified);
  size_t PerformClassification(
      std::vector<std::vector<int>> &image_to_be_classified);
  size_t PerformClassification(const std::string &image_classifying_file);

  /**
   * Perform an accuracy check of a trained model.
   */
  double PerformModelAccuracyTest(const std::string &image_classifying_file,
                                  const std::string &label_file);

 private:
  /**
   * Writes the trained model to a file.
   */
  bool WriteToFile(const std::string &file);

  Model trained_model_;
  std::string default_model_storing_file =
      "/Users/ravipatel/Desktop/cinder_0.9.2_mac/my-projects/"
      "naivebayes-RaviPatel1713/data/scrape.txt";
};
}  // namespace naivebayes

#endif  // NAIVE_BAYES_NAIVE_BAYES_CLASSIFIER_H
