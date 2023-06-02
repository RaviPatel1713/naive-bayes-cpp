#include "core/naive_bayes_classifier.h"
#include <iostream>
#include "core/model.h"
#include <cmath>

namespace naivebayes {
// d - variable type(double) vec - data structure _3d - 3 dimensional vector
using dvec_3d = std::vector<std::vector<std::vector<double>>>;

NaiveBayesClassifier::NaiveBayesClassifier(
    const std::string &image_file, const std::string &image_label_file,
    const std::string &model_to_save_file, const double k_laplace) {
  // generate datasets from image and labels provided and makes a model object
  trained_model_ = Model(image_file, image_label_file, k_laplace);

  // writes the trained model into a file provided
  WriteToFile(model_to_save_file);
}

NaiveBayesClassifier::NaiveBayesClassifier(
    const std::string &image_file, const std::string &image_label_file,
    const std::string &model_to_save_file)
    : NaiveBayesClassifier(image_file, image_label_file, model_to_save_file,
                           1.0) {
}

NaiveBayesClassifier::NaiveBayesClassifier(const std::string &image_file,
                                           const std::string &image_label_file)
    : NaiveBayesClassifier(image_file, image_label_file,
                           default_model_storing_file, 1.0) {
}

NaiveBayesClassifier::NaiveBayesClassifier(
    const std::string &saved_model_file) {
  if (saved_model_file.empty()) {
    std::cout << "The file path provided is empty." << std::endl;
    return;
  }

  std::ifstream file_reader;
  file_reader.open(saved_model_file);

  if (!file_reader) {
    std::cout << "The file cannot be opened." << std::endl;
    return;
  }

  file_reader >> trained_model_;
  file_reader.close();
}

NaiveBayesClassifier::NaiveBayesClassifier(const std::string &image_file,
                                           const std::string &image_label_file,
                                           const double k_laplace)
    : NaiveBayesClassifier(image_file, image_label_file,
                           default_model_storing_file, k_laplace) {
}

bool NaiveBayesClassifier::WriteToFile(const std::string &file) {
  std::ofstream file_writer;
  file_writer.open(file);
  if (!file_writer)
    return false;

  file_writer << trained_model_;
  file_writer.close();
  return true;
}

size_t NaiveBayesClassifier::PerformClassification(
    Image &image_to_be_classified) {
//  std::cout << trained_model_.GetImageSize() << std::endl;
  if(image_to_be_classified.size() != trained_model_.GetImageSize()){
    std::cout << "The image is incorrect for trained model.\n";
    std::cout << "The trained model is of image size "
              << trained_model_.GetImageSize() << "." << std::endl;
    return -INT_MAX;
  }
  std::vector<double> likelihood_scores;
  std::vector<double> class_prior_probabilities =
      trained_model_.GetClassPriorProbabilities();
  dvec_3d feature_probability_matrix =
      trained_model_.GetFeatureProbabilityMatrix();

  for (size_t c = 0; c < class_prior_probabilities.size(); ++c) {
    double current_likelihood_score = log10(class_prior_probabilities[c]);
    for (size_t row = 0; row < 28; ++row) {
      for (size_t col = 0; col < 28; ++col) {
        if (image_to_be_classified.at(row, col) == 1) {
          current_likelihood_score +=
              log10(feature_probability_matrix[c][row][col]);
        } else {
          current_likelihood_score +=
              log10(1 - feature_probability_matrix[c][row][col]);
        }
      }
    }
    likelihood_scores.push_back(current_likelihood_score);
  }

  double most_likelihood_class = 0;
  for (size_t c = 0; c < likelihood_scores.size(); ++c) {
    if (likelihood_scores.at(most_likelihood_class) < likelihood_scores.at(c)) {
      most_likelihood_class = c;
    }
  }
  return most_likelihood_class;
}


size_t NaiveBayesClassifier::PerformClassification(
    std::vector<std::vector<int>> &image_to_be_classified) {
  Image image_data = Image(image_to_be_classified);
  return PerformClassification(image_data);
}

size_t NaiveBayesClassifier::PerformClassification(
    const std::string &image_classifying_file) {
  Image image_data;
  std::ifstream reader;
  reader.open(image_classifying_file);
  reader >> image_data;
  reader.close();
  return PerformClassification(image_data);
}
double NaiveBayesClassifier::PerformModelAccuracyTest(
    const std::string &image_classifying_file, const std::string &label_file) {
  size_t accuracy_count = 0, dataset_size = 0;
  std::ifstream image_reader, label_reader;
  image_reader.open(image_classifying_file);
  label_reader.open(label_file);

  while(!image_reader.eof() && !label_reader.eof()){
    dataset_size = dataset_size + 1;
    naivebayes::Image image;
    image_reader >> image;

    size_t label_type;
    label_reader >> label_type;

    int class_type = PerformClassification(image);
    if (class_type < 0) return 0.0; // invalid image or image size classified

    if (label_type == class_type) accuracy_count = accuracy_count + 1;
  }
  return static_cast<double>(accuracy_count) / static_cast<double>(dataset_size);
}
}  // namespace naivebayes