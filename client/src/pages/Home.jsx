import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import '../css/HomePage.css';

function HomePage() {
  const [files, setFiles] = useState([]);
  const navigate = useNavigate();

  const handleFileChange = (e) => {
    setFiles(e.target.files);
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    if (files.length !== 2) {
      alert('Please upload exactly 2 files');
      return;
    }

    const formData = new FormData();
    for (let i = 0; i < 2; i++) {
      formData.append('files', files[i]);
    }

    try {
      const res = await fetch('http://localhost:5000/api/analyze', {
        method: 'POST',
        body: formData
      });

      const data = await res.json();
      navigate('/result', { state: { result: data } });
    } catch (err) {
      alert('Error analyzing files');
    }
  };

  return (
    <div className="homepage">
      <h1>Code Plagiarism Checker</h1>
      <form onSubmit={handleSubmit} className="upload-form">
        <input type="file" onChange={handleFileChange} multiple accept=".cpp" />
        <button type="submit">Check Similarity</button>
      </form>
    </div>
  );
}

export default HomePage;
