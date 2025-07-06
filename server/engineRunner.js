const { execFile } = require('child_process');
const path = require('path');

function runEngine(files) {
  return new Promise((resolve, reject) => {
    const cppBinaryPath = path.join(__dirname,'engine/engine.exe');
    // console.log("Binary Path:", cppBinaryPath);

    const args = files.map(f => f.path);
    // console.log("File paths being sent to C++:", args);


    execFile(cppBinaryPath, args, (err, stdout, stderr) => {
      if (stderr) console.error('STDERR:', stderr);

      try {
        // Remove any leading/trailing whitespace or newlines
        const cleaned = stdout.trim();
        const result = JSON.parse(cleaned);
        result.file1 = files[0].originalname;
        result.file2 = files[1].originalname;
        resolve(result);
      } catch (e) {
        // console.error("STDOUT:\n", stdout);
        // console.error("STDERR:\n", stderr);
        reject('C++ output parsing failed: ' + e.message);
      }
    });
  });
}

module.exports = runEngine;