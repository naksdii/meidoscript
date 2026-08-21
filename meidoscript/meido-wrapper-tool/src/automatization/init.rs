/*
{
  "name": "Pkg",

  "index": "main.mds",

  "version": "1.0.0",

  "license": "MIT",

  "description": "A simple hello-world program",

  "maintainer": "your@email.com",

  "dependencies": ["libc6"],

}
*/

use inquire::{Select, Text};
use serde::{Deserialize, Serialize};
use std::fs;

#[derive(Debug, Deserialize, Serialize)]
pub struct PackageConf {
    pub name: String,
    pub version: String,
    pub license: String,
    pub description: String,
    pub maintainer: String,
    pub dependencies: Vec<String>,
}
pub fn init() {
    adquiring_elements_and_creating_jsonc();
}
fn adquiring_elements_and_creating_jsonc() {
    let name = adquire_value("name");

    let version = adquire_value("version");

    let maintaner = adquire_value("maintaner");

    let description = adquire_value("description");

    let options = vec![
        "UNLICENSED",
        "MIT",
        "GPL-3.0",
        "BSD-2-Clause",
        "BSD-3-Clause",
        "Apache-2.0",
    ];
    let license = Select::new("Choose a license", options)
        .prompt()
        .unwrap_or_else(|err| {
            eprintln!("Error at defining license: {:#?}", err);
            std::process::exit(1);
        });
    println!("when typing the dependencing use comma to separate all of them\n(lib1,lib2,lib3)");
    let dependencies: String = adquire_value("dependencies");
    let dependencies: Vec<String> = dependencies
        .split(",")
        .map(|item| item.trim())
        .filter(|item| item.is_empty())
        .map(|item| item.to_string())
        .collect();

    jsonc_create(
        name,
        version,
        description,
        maintaner,
        license.to_string(),
        dependencies,
    );
}
fn adquire_value(val: &str) -> String {
    let buffer: String = format!(
        "What's the package {}?\n[If left in blank, default option will be used]",
        val
    );
    let val = Text::new(&buffer)
        .with_default(val)
        .prompt()
        .unwrap_or_else(|err| {
            eprintln!("error at adquire a value: {:#?}", err);
            std::process::exit(1);
        });
    val
}

fn jsonc_create(
    name: String,
    version: String,
    description: String,
    maintaner: String,
    license: String,
    dependencies: Vec<String>,
) {
    let json_file: PackageConf = PackageConf {
        name: (name.clone()),
        version: (version),
        license: (license),
        description: (description),
        maintainer: (maintaner),
        dependencies: (dependencies),
    };
    create_workspace(name, json_file);
}

fn create_workspace(name: String, json_file: PackageConf) {
    let path = format!("{name}/"); // cria caminho do diretorio a ser criado
    if let Err(err) = fs::create_dir(path) {
        // cria o diretorio
        eprintln!("path isn't valid {:#?} ", err);
        return;
    } // para o codigo caso tenha erros
    let path = format!("{name}/src");
    if let Err(err) = fs::create_dir(path) {
        eprintln!("path isn't valid {:#?}", err);
        return;
    }
    let buff = format!("{name}/src/main.mds");
    if let Err(err) = fs::write(
        buff,
        "import io from std;\nfun void main()\n{\n   io.print('hello wordl!');\n   io.flush();\n};\nmain();",
    ) {
        eprintln!("Error writing main: {:#?}", err);
        return;
    }
    let path = format!("{name}/debug");
    if let Err(err) = fs::create_dir(path) {
        eprintln!("failed to create debug directory: {:#?}", err);
        return;
    };
    let path = format!("{name}/config.json");
    let file = fs::File::create(path).unwrap_or_else(|err| {
        eprintln!("failed to create json: {:#?}", err);
        std::process::exit(1);
    });
    serde_json::to_writer_pretty(file, &json_file).unwrap_or_else(|err| {
        eprintln!("failed to write in json: {:#?}", err);
        std::process::exit(1)
    });
}
