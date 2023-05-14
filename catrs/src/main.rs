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
        eprintln!("Usage: cat <file>");
        eprintln!("File argument required 🐢");
        std::process::exit(1);
    }

    let mut file = File::new(&args[1]);

    file.read();

    println!("{}", file.contents);
}
