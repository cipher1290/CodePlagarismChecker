import React from 'react';
import { useLocation, useNavigate } from 'react-router-dom';
import '../css/ResultPage.css';

function ResultPage() {
  const location = useLocation();
  const navigate = useNavigate();
  const result = location.state?.result;

  if (!result) {
    return (
      <div className="result-page">
        <h2>No result found</h2>
        <button onClick={() => navigate('/')}>Go Back</button>
      </div>
    );
  }

  return (
    <div className="result-page">
      <h1>Analysis Result</h1>
      <ul>
        <li><strong>Tokens in File 1:</strong> {result.tokens_file1}</li>
        <li><strong>Tokens in File 2:</strong> {result.tokens_file2}</li>
        <li><strong>LCS Length:</strong> {result.LCS_length}</li>
        <li><strong>Similarity:</strong> {result.similarity.toFixed(2)}%</li>
        <li><strong>Plagiarized:</strong> {result.plagiarized ? 'Yes' : 'No'}</li>
      </ul>
      <button onClick={() => navigate('/')}>Check Again</button>
    </div>
  );
}

export default ResultPage;
