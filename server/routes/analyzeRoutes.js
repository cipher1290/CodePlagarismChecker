const express = require('express');
const router = express.Router();
const multer = require('multer');
const path = require('path');
const runEngine = require('../engineRunner');

// upload config in multer
const upload = multer({ dest: path.join(__dirname, '../uploads/') });

router.post('/analyze', upload.array('files'), async (req, res) => {
  try {
    const files = req.files;

    if (!files || files.length < 2) {
      return res.status(400).json({ error: 'Please upload at least two files.' });
    }

    const result = await runEngine(files); // getting result from cpp
    res.json(result);
  } catch (err) {
    console.error('Backend error:', err);
    res.status(500).json({ error: 'Server error' });
  }
});

module.exports = router;
