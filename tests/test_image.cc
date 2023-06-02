#include <catch2/catch.hpp>

#include <core/image.h>
#include <fstream>

using naivebayes::Image;

//TEST_CASE("28 x 28 image_data tester") {
//  std::vector<std::string> valid_image_in_str ={"                            ",
//                                                "                            ",
//                                                "                            ",
//                                                "                            ",
//                                                "                            ",
//                                                "                            ",
//                                                "                            ",
//                                                "             111111         ",
//                                                "             1111111        ",
//                                                "            11111111        ",
//                                                "            11111111        ",
//                                                "           111  1111        ",
//                                                "           111111111        ",
//                                                "           111111111        ",
//                                                "           111111111        ",
//                                                "            1111111         ",
//                                                "              11111         ",
//                                                "              1111          ",
//                                                "              1111          ",
//                                                "            11111           ",
//                                                "            1111            ",
//                                                "           1111             ",
//                                                "          1111              ",
//                                                "         1111               ",
//                                                "         111                ",
//                                                "        111                 ",
//                                                "        111                 ",
//                                                "                            "};
//  Image image_data, image_data_2;
//
//  SECTION("test image extraction operator overloading") {
//    bool expected = true;
//
//    std::string file;
//    std::ifstream file_reader;
//    file_reader.open(file);
//    file_reader >> image_data;
//    file_reader.close();
//    for (size_t row = 0; row < image_data.size(); ++row){
//      for (size_t col = 0; col < image_data.size(); ++col) {
//        if (image_data.at(row, col) != valid_image_in_str.at(row).at(col)){
//          expected = false;
//          break;
//        }
//      }
//      if (!expected) break;
//    }
//    REQUIRE(expected == true);
//
//  }
//  SECTION("test image insertion operator overloading") {
//    bool expected = false;
//
//    //file writer
//    std::ofstream file_writer;
//    file_writer.open("/Users/ravipatel/Desktop/cinder_0.9.2_mac/my-projects/"
//                        "naivebayes-RaviPatel1713/tests/testing_dataset_dir/"
//                        "testing_image_class_file");
//    file_writer << image_data;
//    file_writer.close();
//
//    //file reader
//    std::ifstream file_reader;
//    file_reader.open("/Users/ravipatel/Desktop/cinder_0.9.2_mac/my-projects/"
//                        "naivebayes-RaviPatel1713/tests/testing_dataset_dir/"
//                        "testing_image_class_file");
//    file_reader >> image_data_2;
//    file_reader.close();
//
//    if (image_data == image_data_2) expected = true;
//
//    REQUIRE(expected == true);
//  }
//
//}

