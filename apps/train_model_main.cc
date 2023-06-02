#include <iostream>
#include <string>
#include <core/naive_bayes_classifier.h>
#include <core/image.h>

#include "cl_parser.cc"

// --train /Users/ravipatel/Desktop/cinder_0.9.2_mac/my-projects/naivebayes-RaviPatel1713/data/mnistdatatraining/trainingimages /Users/ravipatel/Desktop/cinder_0.9.2_mac/my-projects/naivebayes-RaviPatel1713/data/mnistdatatraining/traininglabels --save /Users/ravipatel/Desktop/cinder_0.9.2_mac/my-projects/naivebayes-RaviPatel1713/data/trained_model_file
// -ld /Users/ravipatel/Desktop/cinder_0.9.2_mac/my-projects/naivebayes-RaviPatel1713/data/trained_model_file -ca /Users/ravipatel/Desktop/cinder_0.9.2_mac/my-projects/naivebayes-RaviPatel1713/data/mnistdatavalidation/testimages /Users/ravipatel/Desktop/cinder_0.9.2_mac/my-projects/naivebayes-RaviPatel1713/data/mnistdatavalidation/testlabels
using namespace std;
using naivebayes::NaiveBayesClassifier;

int main(int argc, char *argv[]) {
  /*
  // Declare the supported options.
  int var2;
  po::options_description desc("Allowed options");
  desc.add_options()
      ("help,h", "produce help message")
      ("train,tr", po::value<std::string>(), "get training data")
      ("var2", po::value<int>(&var2)->default_value(10), "set var2")
      ("string1", po::value<string>(), "set string1")
      ("list1", po::value< vector<string> >(), "set list1")
      ("input-file", po::value< vector<string> >(), "set input files")
      ;

  // Declare which options are positional
  po::positional_options_description p;
  p.add("input-file", -1);

  po::variables_map vm;
  // parse regular options
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  // parse positional options
  po::store(po::command_line_parser(argc, argv).
  options(desc).positional(p).run(), vm); po::notify(vm);

  if (vm.count("help")) {
    cout << desc << endl;
    return 1;
  }

  if (vm.count("var1")) {
    cout << "var1 was set to "
         << vm["var1"].as<int>() << ".\n";
  } else {
    cout << "var1 was not set.\n";
  }

  if (vm.count("var2")) {
    cout << "var2 was set to "
         << vm["var2"].as<int>() << ".\n";
  }

  if (vm.count("string1")) {
    cout << "string1 was set to " << vm["string1"].as<string>() << ".\n";
  }

  if (vm.count("list1")) {
    cout << "list1 is: " << endl;
    for(int i = 0; i < vm["list1"].as< vector<string> >().size(); i++)
      cout << vm["list1"].as< vector<string> >()[i] << endl;
  }

  if (vm.count("input-file")) {
    cout << "input files are: " << endl;
    for(int i = 0; i < vm["input-file"].as< vector<string> >().size(); i++)
      cout << vm["input-file"].as< vector<string> >()[i] << endl;
  }
  return EXIT_SUCCESS;
   */
  string image_file = "";
  string label_file = "";
  string model_to_save_file = "";
  string trained_model_file = "";
  string image_classifying_file = "";
  string image_file_for_accuracy = "";
  string label_file_for_accuracy = "";


  /*
   * iamge, label, save classify
   * iamge, label, save
   *
   * load, classify test
   *
   */

  bool parsed_successfully = cl_parser::ParseCommandLine(argc, argv,
                              image_file,
                              label_file,
                              model_to_save_file,
                              trained_model_file,
                              image_classifying_file,
                              image_file_for_accuracy,
                              label_file_for_accuracy);
  cout << (parsed_successfully ? "true" : "false") << endl;
  cout << "image file:" << image_file << endl;
  cout << "label file:" << label_file << endl;
  cout << "save file:" << model_to_save_file << endl;
  cout << "trained model file:" << trained_model_file << endl;
  cout << "image classifying file:" << image_classifying_file << endl;
  cout << "image file for accuracy:" << image_file_for_accuracy << endl;
  cout << "label file for accuracy:" << label_file_for_accuracy << endl;

  if (!parsed_successfully) return -1;

  naivebayes::NaiveBayesClassifier classifier;

  if (!image_file.empty() &&        // found arg for image data
      !label_file.empty() &&        // found arg for label data
      !model_to_save_file.empty()) {  // found arg for saving model
    cout << "What is the klaplace smoothing factor? range-[0.00001, 10000] ";
    double k = 0.0;
    cin >> k;
    if (k < 0.00001 || k > 10000) {
      cout << "Invalid. The k-laplace is invalid.\n";
      return 0;
    }

    classifier =
        NaiveBayesClassifier(image_file, label_file, model_to_save_file, k);
    if (!image_classifying_file
             .empty()) {  // found arg for images classification
      cout << "The classified image is "
           << classifier.PerformClassification(image_classifying_file) << "."
           << endl;
    }
    cout << "The model is successfully trained. You can now classify images\n";
    return 0;
  }

  if (!trained_model_file.empty() &&      // found arg for loading trained model
      !image_classifying_file.empty() &&  // found are for images classification
      // found arg for validating and checking accuracy
      !image_file_for_accuracy.empty() && !label_file_for_accuracy.empty()) {
    classifier = NaiveBayesClassifier(trained_model_file);
    cout << "The classified image is "
         << classifier.PerformClassification(image_classifying_file) << "."
         << endl;

    double accuracy_percent =
        classifier.PerformModelAccuracyTest(image_file_for_accuracy,
                                            label_file_for_accuracy) *
        100;
    cout << "The trained model has accuracy of " << accuracy_percent << "."
         << endl;
    return 0;
  }

  if (!trained_model_file.empty() &&      // found arg for loading trained model
      !image_classifying_file.empty()) {  // found are for images classification
    classifier = NaiveBayesClassifier(trained_model_file);
    cout << "The classified image is "
         << classifier.PerformClassification(image_classifying_file) << "."
         << endl;
    return 0;
  }

  if (!trained_model_file.empty() &&  // found arg for loading trained model
       // found arg for validating and checking accuracy
      !image_file_for_accuracy.empty() &&
      !label_file_for_accuracy.empty()) {
    classifier = NaiveBayesClassifier(trained_model_file);
    double accuracy_percent =
        classifier.PerformModelAccuracyTest(image_file_for_accuracy,
                                            label_file_for_accuracy) *
        100;
    cout << "The trained model has accuracy of " << accuracy_percent << "."
         << endl;
    return 0;
  }
}
