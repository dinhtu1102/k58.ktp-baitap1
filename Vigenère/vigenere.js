const ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// ------------------ Validation ------------------
function validateInput(text, key) {
  if (!text || !key) return "Vui lòng nhập đầy đủ văn bản và khóa.";
  if (!/^[A-Z\s]*$/.test(text)) return "Văn bản chỉ chứa chữ hoa A-Z và khoảng trắng.";
  if (!/^[A-Z]+$/.test(key)) return "Khóa phải là chữ hoa A-Z, không có khoảng trắng.";
  return null;
}

// ------------------ Vigenère Encrypt ------------------
function encryptVigenere() {
  const input = document.getElementById("plain").value.toUpperCase();
  const key = document.getElementById("key").value.toUpperCase();

  const err = validateInput(input, key);
  if (err) { showError(err); return; }

  const m = key.length;
  let cipher = '';
  let logDetail = [];

  for (let i = 0; i < input.length; i++) {
    const ch = input[i];
    if (ch === " ") { cipher += " "; logDetail.push("(khoảng trắng)"); continue; }
    const p = ALPHABET.indexOf(ch);
    const k = ALPHABET.indexOf(key[i % m]);
    const c = (p + k) % 26;
    cipher += ALPHABET[c];
    logDetail.push(`${ch}(${p}) + ${key[i % m]}(${k}) mod 26 = ${ALPHABET[c]}(${c})`);
  }

  document.getElementById("stepsBox").style.display = "block";
  document.getElementById("log1").innerHTML = `<b>Bước 1:</b> Chuyển ký tự sang số và cộng khóa`;
  document.getElementById("log2").innerHTML = `<ul>${logDetail.map(l => `<li>${l}</li>`).join('')}</ul>`;
  document.getElementById("log3").innerHTML = `<b>Bước 2:</b> Ghép kết quả thành ciphertext: ${cipher}`;
  document.getElementById("final").innerHTML = `<div class="result">Kết quả mã hóa: <b>${cipher}</b></div>`;
}

// ------------------ Vigenère Decrypt ------------------
function decryptVigenere() {
  const input = document.getElementById("plain").value.toUpperCase();
  const key = document.getElementById("key").value.toUpperCase();

  const err = validateInput(input, key);
  if (err) { showError(err); return; }

  const m = key.length;
  let plain = '';
  let logDetail = [];

  for (let i = 0; i < input.length; i++) {
    const ch = input[i];
    if (ch === " ") { plain += " "; logDetail.push("(khoảng trắng)"); continue; }
    const c = ALPHABET.indexOf(ch);
    const k = ALPHABET.indexOf(key[i % m]);
    const p = (c - k + 26) % 26;
    plain += ALPHABET[p];
    logDetail.push(`${ch}(${c}) - ${key[i % m]}(${k}) + 26 mod 26 = ${ALPHABET[p]}(${p})`);
  }

  document.getElementById("stepsBox").style.display = "block";
  document.getElementById("log1").innerHTML = `<b>Bước 1:</b> Chuyển ký tự sang số và trừ khóa`;
  document.getElementById("log2").innerHTML = `<ul>${logDetail.map(l => `<li>${l}</li>`).join('')}</ul>`;
  document.getElementById("log3").innerHTML = `<b>Bước 2:</b> Ghép kết quả thành plaintext: ${plain}`;
  document.getElementById("final").innerHTML = `<div class="result">Kết quả giải mã: <b>${plain}</b></div>`;
}

// ------------------ Error ------------------
function showError(msg) {
  document.getElementById("log1").innerHTML = `<div class="error">${msg}</div>`;
  document.getElementById("log2").innerHTML = "";
  document.getElementById("log3").innerHTML = "";
  document.getElementById("final").innerHTML = "";
}
