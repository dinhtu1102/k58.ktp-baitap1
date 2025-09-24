/* columnar.js */

// ------------------ Validation ------------------
function validateInput(text, key) {
  if (!text || !key) return "Vui lòng nhập đầy đủ văn bản và khóa.";
  if (!/^[A-Z\s]*$/.test(text)) return "Văn bản chỉ được chứa chữ hoa A-Z và khoảng trắng.";
  if (!/^[A-Z]+$/.test(key)) return "Khóa phải là chữ hoa A-Z, không có khoảng trắng.";
  return null;
}

// ------------------ Columnar Encrypt ------------------
function encryptColumnar() {
  const input = document.getElementById("plain").value.toUpperCase().replace(/\s+/g,'');
  const key = document.getElementById("key").value.toUpperCase();

  const err = validateInput(input, key);
  if (err) { showError(err); return; }

  const m = key.length;
  const rows = Math.ceil(input.length / m);
  const matrix = Array.from({length: rows}, (_, i) => {
    return input.slice(i*m, i*m + m).padEnd(m, 'X').split('');
  });

  // Tạo thứ tự cột theo khóa
  const keyOrder = key.split('').map((ch, idx) => ({ch, idx}))
                         .sort((a,b) => a.ch.localeCompare(b.ch))
                         .map(obj => obj.idx);

  // Đọc cột theo thứ tự keyOrder
  let cipher = '';
  for (let col of keyOrder) {
    for (let r = 0; r < rows; r++) {
      cipher += matrix[r][col];
    }
  }

  // Hiển thị log
  document.getElementById("stepsBox").style.display = "block";
  document.getElementById("log1").innerHTML = `<b>Bảng chữ cái theo hàng:</b><br>${matrix.map(r=>r.join(' ')).join('<br>')}`;
  document.getElementById("log2").innerHTML = `<b>Thứ tự cột theo khóa:</b> [${keyOrder.join(', ')}]`;
  document.getElementById("log3").innerHTML = `<b>Đọc cột theo thứ tự khóa:</b> ${cipher}`;
  document.getElementById("final").innerHTML = `<div class="result">Kết quả mã hóa: <b>${cipher}</b></div>`;
}

// ------------------ Columnar Decrypt ------------------
function decryptColumnar() {
  const cipher = document.getElementById("plain").value.toUpperCase().replace(/\s+/g,'');
  const key = document.getElementById("key").value.toUpperCase();

  const err = validateInput(cipher, key);
  if (err) { showError(err); return; }

  const m = key.length;
  const rows = Math.ceil(cipher.length / m);
  const keyOrder = key.split('').map((ch, idx) => ({ch, idx}))
                         .sort((a,b) => a.ch.localeCompare(b.ch))
                         .map(obj => obj.idx);

  // Tạo ma trận rỗng
  const matrix = Array.from({length: rows}, () => Array(m).fill(''));

  // Chia cipher theo cột
  let k = 0;
  for (let col of keyOrder) {
    for (let r = 0; r < rows; r++) {
      matrix[r][col] = cipher[k++] || 'X';
    }
  }

  // Đọc theo hàng
  let plain = matrix.map(r => r.join('')).join('');

  // Hiển thị log
  document.getElementById("stepsBox").style.display = "block";
  document.getElementById("log1").innerHTML = `<b>Bảng chữ cái theo cột:</b><br>${matrix.map(r=>r.join(' ')).join('<br>')}`;
  document.getElementById("log2").innerHTML = `<b>Thứ tự cột theo khóa:</b> [${keyOrder.join(', ')}]`;
  document.getElementById("log3").innerHTML = `<b>Đọc theo hàng:</b> ${plain}`;
  document.getElementById("final").innerHTML = `<div class="result">Kết quả giải mã: <b>${plain}</b></div>`;
}

// ------------------ Error ------------------
function showError(msg) {
  document.getElementById("log1").innerHTML = `<div class="error">${msg}</div>`;
  document.getElementById("log2").innerHTML = "";
  document.getElementById("log3").innerHTML = "";
  document.getElementById("final").innerHTML = "";
}
