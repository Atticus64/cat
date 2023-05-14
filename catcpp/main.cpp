#include <fstream>
#include <iostream>
#include <optional>
#include <string_view>

class FileGuard {
public:
  FileGuard(const std::string_view path) { my_file.open(path.data()); }

  ~FileGuard() { my_file.close(); }

  auto data() noexcept -> std::ifstream & { return my_file; }

  auto read_file() noexcept -> std::string {

    std::string fileBuffer;
    std::string currentLine;

    while (std::getline(my_file, currentLine)) {
      fileBuffer += currentLine + '\n';
    }

    return fileBuffer;
  }

private:
  std::ifstream my_file;
};

auto fetchFile(std::string filename) -> std::optional<std::string> {
  FileGuard file(filename.data());

  if (!file.data()) {
    std::cout << "Failed to open file " << filename;
    return {};
  }

  return file.read_file();
}

auto handleArgMissing() {
  std::cerr << "Usage: cat <filename> " << std::endl;
  std::cerr << "File argument required 🐢" << std::endl;
}

int main(int argc, char *argv[]) {

  if (argc < 2) {
    handleArgMissing();
    return EXIT_FAILURE;
  }

  auto data = fetchFile(argv[1]);

  std::cout << data.value_or("File not found") << std::endl;

  return 0;
}
