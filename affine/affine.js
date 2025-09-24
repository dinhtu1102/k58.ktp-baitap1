const ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/* ------------------ Math Helpers ------------------ */
function gcd(a, b) {
  return b === 0 ? a : gcd(b, a % b);
}

function modInverse(a, m) {
  a = ((a % m) + m) % m;
  for (let i = 1; i < m; i++) {
    if ((a * i) % m === 1) return i;
  }
  return null;
}

/* ------------------ Validation ------------------ */
function validateInput(text, a, b) {
  if (!text || isNaN(a) || isNaN(b)) return "Vui lòng nhập đầy đủ văn bản và khóa.";
  if (!/^[A-Z\s]*$/.test(text)) return "Chỉ chấp nhận chữ hoa A-Z và khoảng trắng.";
  if (gcd(a, 26) !== 1) return "Khóa a không hợp lệ: phải cùng nguyên tố với 26.";
  return null;
}

/* ------------------ Affine Encrypt & Decrypt ------------------ */
function encrypt(text, a, b) {
  return [...text].map(ch => {
    if (ch === " ") return " ";
    let idx = ALPHABET.indexOf(ch);
    return ALPHABET[(a * idx + b) % 26];
  }).join("");
}

function decrypt(text, a, b) {
  const inv = modInverse(a, 26);
  if (inv === null) return null;
  return [...text].map(ch => {
    if (ch === " ") return " ";
    let idx = ALPHABET.indexOf(ch);
    return ALPHABET[(inv * (idx - b + 26)) % 26];
  }).join("");
}

/* ------------------ Display Steps ------------------ */
function showError(msg) {
  document.getElementById("log1").innerHTML = `<div class="error">${msg}</div>`;
  document.getElementById("log2").innerHTML = "";
  document.getElementById("log3").innerHTML = "";
  document.getElementById("final").innerHTML = "";
}

function showEncryptSteps(input, a, b) {
  document.getElementById("stepsBox").style.display = "block";

  let numArr = [...input].map(ch => ch === " " ? " " : ALPHABET.indexOf(ch));
  let encArr = numArr.map(n => n === " " ? " " : (a * n + b) % 26);
  let cipher = encrypt(input, a, b);

  document.getElementById("log1").innerHTML = `<b>Bước 1:</b> Chuyển chữ sang số: [${numArr.join(", ")}]`;

  let detail = encArr.map((n, i) => n === " " ? "<li>(khoảng trắng)</li>" : `<li>(${a} * ${numArr[i]} + ${b}) mod 26 = ${n}</li>`).join("");
  document.getElementById("log2").innerHTML = `<b>Bước 2:</b> Áp dụng công thức C = (a*P + b) mod 26<ul>${detail}</ul>`;

  document.getElementById("log3").innerHTML = `<b>Bước 3:</b> Chuyển số sang chữ: ${cipher}`;
  document.getElementById("final").innerHTML = `<div class="result">Kết quả mã hóa: <b>${cipher}</b></div>`;
}

function showDecryptSteps(input, a, b) {
  document.getElementById("stepsBox").style.display = "block";

  const inv = modInverse(a, 26);
  let numArr = [...input].map(ch => ch === " " ? " " : ALPHABET.indexOf(ch));
  let decArr = numArr.map(n => n === " " ? " " : (inv * (n - b + 26)) % 26);
  let plain = decrypt(input, a, b);

  document.getElementById("log1").innerHTML = `<b>Bước 1:</b> Chuyển ký tự sang số: [${numArr.join(", ")}], a⁻¹ = ${inv}`;
  let detail = decArr.map((n, i) => n === " " ? "<li>(khoảng trắng)</li>" : `<li>${inv} * (${numArr[i]} - ${b}) mod 26 = ${n}</li>`).join("");
  document.getElementById("log2").innerHTML = `<b>Bước 2:</b> Tính P = a⁻¹ * (C - b) mod 26<ul>${detail}</ul>`;
  document.getElementById("log3").innerHTML = `<b>Bước 3:</b> Chuyển số sang chữ: ${plain}`;
  document.getElementById("final").innerHTML = `<div class="result">Kết quả giải mã: <b>${plain}</b></div>`;
}

/* ------------------ Main Functions ------------------ */
function encryptAffine() {
  const input = document.getElementById("plain").value.toUpperCase().trim();
  const a = parseInt(document.getElementById("keyA").value);
  const b = parseInt(document.getElementById("keyB").value);

  const err = validateInput(input, a, b);
  if (err) { showError(err); return; }
  showEncryptSteps(input, a, b);
}

function decryptAffine() {
  const input = document.getElementById("plain").value.toUpperCase().trim();
  const a = parseInt(document.getElementById("keyA").value);
  const b = parseInt(document.getElementById("keyB").value);

  const err = validateInput(input, a, b);
  if (err) { showError(err); return; }
  showDecryptSteps(input, a, b);
}
