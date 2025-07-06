// src/components/UploadForm.js
import React, { useState } from 'react';
import axios from 'axios';
import { useNavigate } from 'react-router-dom';

const UploadForm = () => {
  const [files, setFiles] = useState([]);
  const [error, setError] = useState('');
  const navigate = useNavigate();

  const handleFileChange = (e) => {
    setFiles(e.target.files);
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    if (files.length !== 2) {
      setError('Please upload exactly two .cpp files.');
      return;
    }

    const formData = new FormData();
    formData.append('files', files[0]);
    formData.append('files', files[1]);

    try {
      const res = await axios.post('http://localhost:5000/api/analyze', formData);
      navigate('/result', { state: res.data }); // pass data to Result page
    } catch (err) {
      setError('Something went wrong during analysis.');
    }
  };

  return (
    <form onSubmit={handleSubmit}>
      <input type="file" onChange={handleFileChange} multiple accept=".cpp" />
      <button type="submit">Analyze</button>
      {error && <p style={{ color: 'red' }}>{error}</p>}
    </form>
  );
};

export default UploadForm;
