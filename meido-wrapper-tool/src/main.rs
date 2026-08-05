use std::env;

use crate::automatization::init::init;
mod automatization;

fn main() {
    let arguments: Vec<String> = env::args().collect();

    let mut l = 1;
    while l < 2 {
        if arguments.get(l).is_none() {
            println!("Sem argumentos o suficiente para executar uma ação");
            return;
        }
        l += 1;
    }

    if arguments[1] == "init" {
        init();
    }
}
