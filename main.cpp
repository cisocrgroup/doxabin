#include <unistd.h>
#include <opencv2/opencv.hpp>
// local includes in gsm/Doxa
#include "Doxa/Image.hpp"
#include "Doxa/Parameters.hpp"
#include "Doxa/ISauvola.hpp"
#include "Doxa/PNM.hpp"

struct args {
  char *inf;
  char *outf;
  double k;
  int w;
};

int parse(int argc, char **argv, args& args) {
  int option;
  while((option = getopt(argc, argv, ":k:w:")) != -1) {
    switch (option) {
    case 'k':
      args.k = strtod(optarg, nullptr);
      break;
    case 'w':
      args.w = atoi(optarg);
      break;
    default:
      return 1;
    }
  }
  if (optind >= argc) {
    return 1;
  }
  args.inf = argv[optind++];
  if (optind >= argc) {
    return 1;
  }
  args.outf = argv[optind++];
  if (optind < argc) {
    return 1;
  }
  return 0;
}

int main(int argc, char **argv) {
  // Handle command line args.
  struct args args = {nullptr, nullptr, 0.2, 75};
  if (parse(argc, argv, args) != 0) {
    std::cerr << "Usage: " << argv[0] << " [Options] IN OUT\n";
    std::cerr << "Options:\n";
    std::cerr << " -k n\tset k-value (default: 0.2)\n";
    std::cerr << " -w n\tset window size (default: 75)\n";
    return EXIT_FAILURE;
  }

  // Read image and convert it into gray scale.
  auto img = cv::imread(args.inf);
  cv::Mat graymat;
  cv::cvtColor(img, graymat, cv::COLOR_BGR2GRAY);
  assert(graymat.channels() == 1);
  std::vector<Doxa::Pixel8> buf(graymat.begin<Doxa::Pixel8>(), graymat.end<Doxa::Pixel8>());

  // Binarize the image.
  const auto w = graymat.cols;
  const auto h = graymat.rows;
  const auto image = Doxa::Image::Reference(w, h, buf.data());
  Doxa::Parameters parameters(Doxa::ParameterMap({{"window", args.w}}));
  parameters.Set("k", args.k);
  Doxa::Image binaryImage = Doxa::ISauvola::ToBinaryImage(image, parameters);
  cv::Mat binmat(h, w, CV_8UC1, binaryImage.data);
  cv::imwrite(args.outf, binmat);
  return EXIT_SUCCESS;
}
