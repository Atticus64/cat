
# Cat implementation in Rust and Cpp

For learning purposes 🤠

<img src="./cat.jpg" width="400px">


## Build cat rust version 

```
cd catrs
```

```
cargo run -- foo.txt
```

## Build cat cpp version

```
cd catcpp
```

```
make && ./cat foo.txt
```

### Rust code

```rust
use std::env;
use std::fs::read_to_string;

struct File {
    path: String,
    contents: String,
}

impl File {
    fn new(path: &str) -> File {
        File {
            path: path.to_owned(),
            contents: String::from(""),
        }
    }

    fn read(&mut self) {
        match read_to_string(&self.path) {
            Ok(cont) => self.contents = cont,
            Err(_) => {
                eprintln!("Error reading file: {}", self.path);
                eprintln!("Probably does not exist 😢");
                std::process::exit(1);
            }
        };
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() != 2 {
        eprintln!("Usage: {} <file>", args[0]);
        std::process::exit(1);
    }

    let mut file = File::new(&args[1]);

    file.read();

    println!("{}", file.contents);
}
```

### Cpp code

```cpp
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
```

If you want to collaborate or share other solution, you can fork and make a pr 


