#include <iostream>
#include <vector>

using namespace std;
namespace cl_parser {

const vector<string> help_commands = {"--help", "-h"};

const vector<string> train_commands = {"--train", "-tr"};
const vector<string> save_commands = {"--save", "-sv"};
const vector<string> classify_commands = {"--classify", "-clsfy"};
const vector<string> load_commands = {"--load", "-ld"};
const vector<string> check_accuracy_commands = {"--check_accuracy", "-ca"};

void printUsageOptions() {
  std::cout << "\nThe following are flags and arguments to train model, "
               "test/classify image(s).\n";
  std::cout << "-tr    --train    [image_data_file_path] "
               "[image_label_data_file_path]\n";
  std::cout << "-sv    --save     [model_saving_file_path]\n";
  std::cout << "-u     --use      [image_data_file_path] "
               "[image_label_data_file_path]\n";
  std::cout << "-clsfy --classify [image(s)_to_be_classified_file_path]\n";
}

bool IsAnotherArgument(const string &str) {
  for (auto e : help_commands) {
    if (str.compare(e) == 0)
      return true;
  }
  for (auto e : train_commands) {
    if (str.compare(e) == 0)
      return true;
  }
  for (auto e : save_commands) {
    if (str.compare(e) == 0)
      return true;
  }
  for (auto e : load_commands) {
    if (str.compare(e) == 0)
      return true;
  }
  for (auto e : classify_commands) {
    if (str.compare(e) == 0)
      return true;
  }
  return false;
}

bool FoundAFlag(const vector<string> &vec, const string &str){
  for (auto e : vec) {
    if (str.compare(e) == 0)
      return true;
  }
  return false;
}

bool ParseCommandLine(int argc, char *argv[], string &image_file,
                     string &label_file, string &model_to_save_file,
                     string &trained_model_file,
                     string &image_classifying_file,
                     string &image_file_for_accuracy,
                     string &label_file_for_accuracy) {
  if (argc == 1) {
    std::cout << "Usage: App <options>\nOptions are:\n";
    std::cout << "-h     --help     ~Provides acceptable command flags and "
                 "argument information.\n";
    printUsageOptions();
    return false;
  }
  if (argc == 2 && FoundAFlag(train_commands, argv[1])) {
    std::cout << "Usage: App <options>\\nOptions are:\\n";
    std::cout << "-h     --help     ~Provides acceptable command flags and "
                 "argument information.\n";
    printUsageOptions();
    return false;
  }

  for (unsigned int i = 1; i < argc; ++i) {
    if (image_file.compare(argv[i]) == 0 || label_file.compare(argv[i]) == 0 ||
        model_to_save_file.compare(argv[i]) == 0 ||
        trained_model_file.compare(argv[i]) == 0 ||
        image_classifying_file.compare(argv[i]) == 0) {
      if (IsAnotherArgument(argv[i])) {
        cout << "Error parsing provided command line arguments.\n";
        return false;
      }
    }

    if (FoundAFlag(check_accuracy_commands, argv[i])) {
      if (i + 2 < argc && image_file.empty() && label_file.empty()) {
        image_file_for_accuracy = argv[i + 1];
        label_file_for_accuracy = argv[i + 2];
      } else {
        cout << "Error parsing provided command line arguments.\n";
        return false;
      }
    }
    else if (FoundAFlag(train_commands, argv[i])) {
      if (i + 2 < argc && image_file.empty() && label_file.empty()) {
        image_file = argv[i + 1];
        label_file = argv[i + 2];
      } else {
        cout << "Error parsing provided command line arguments.\n";
        return false;
      }
    } else if (FoundAFlag(save_commands, argv[i])) {
      if (i + 1 < argc && trained_model_file.empty() &&
          image_classifying_file.empty()) {
        model_to_save_file = argv[i + 1];
      } else {
        cout << "Error parsing provided command line arguments.\n";
        return false;
      }
    } else if (FoundAFlag(classify_commands, argv[i])) {
      if (i + 1 < argc ) {
        image_classifying_file = argv[i + 1];
      } else {
        cout << "Error parsing provided command line arguments.\n";
        return false;
      }
    } else if (FoundAFlag(load_commands, argv[i])) {
      if (i + 1 < argc && image_file.empty() && label_file.empty() && model_to_save_file.empty()) {
        trained_model_file = argv[i + 1];
      } else {
        cout << "Error parsing provided command line arguments.\n";
        return false;
      }
    }
  }
  return true;

  /*
//  NaiveBayesClassifier c = NaiveBayesClassifier(image_data, label_data,
trained_model, 0.0001);

  double accuracy_count = 0;
  std::ifstream reader, reader2;
  reader.open(test_image);
  reader2.open(test_image_label);

  while(!reader.eof()){
    naivebayes::Image image;
    size_t label_type;
    reader >> image;
    reader2 >> label_type;
    NaiveBayesClassifier classifer = NaiveBayesClassifier(trained_model);
    std::pair<size_t, double> result = classifer.PerformClassification(image);

    if (label_type == result.first){
      accuracy_count = accuracy_count + 1;
    }
  }

  std::cout << "\nAccuracy Rate: " << static_cast<double>(accuracy_count/1000.0)
            << std::endl;

  reader.close();
   */
}
}  // namespace cl_parser
