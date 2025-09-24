const ALPHABET = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // J->I

// ------------------ Helpers ------------------
function prepareKey(key) {
  key = key.toUpperCase().replace(/J/g,'I').replace(/[^A-Z]/g,'');
  let seen = new Set();
  let result = '';
  for (let ch of key) if (!seen.has(ch)) { result += ch; seen.add(ch); }
  for (let ch of ALPHABET) if (!seen.has(ch)) { result += ch; seen.add(ch); }
  return result;
}

function makeMatrix(key) {
  key = prepareKey(key);
  let matrix = [];
  for (let i=0;i<5;i++) matrix.push(key.slice(i*5,i*5+5).split(''));
  return matrix;
}

function findPos(matrix, ch) {
  for(let r=0;r<5;r++)
    for(let c=0;c<5;c++)
      if(matrix[r][c]===ch) return [r,c];
  return null;
}

function preprocessPlain(text) {
  text = text.toUpperCase().replace(/J/g,'I').replace(/[^A-Z]/g,'');
  let res = '';
  for(let i=0;i<text.length;i++){
    if(i>0 && text[i]===text[i-1] && res.length%2===1) res+='X';
    res+=text[i];
  }
  if(res.length%2===1) res+='X';
  return res;
}

// ------------------ Validation ------------------
function validateInput(text,key){
  if(!text || !key) return "Vui lòng nhập đầy đủ văn bản và khóa.";
  return null;
}

// ------------------ Encrypt ------------------
function encryptPlayfair(){
  let input = document.getElementById("plain").value;
  let key = document.getElementById("key").value;
  let err = validateInput(input,key);
  if(err){showError(err); return;}

  let matrix = makeMatrix(key);
  let text = preprocessPlain(input);
  let cipher='';
  let logDetail=[];

  for(let i=0;i<text.length;i+=2){
    let a=text[i], b=text[i+1];
    let [r1,c1]=findPos(matrix,a);
    let [r2,c2]=findPos(matrix,b);
    let encA, encB;

    if(r1===r2){ // cùng hàng
      encA = matrix[r1][(c1+1)%5];
      encB = matrix[r2][(c2+1)%5];
    } else if(c1===c2){ // cùng cột
      encA = matrix[(r1+1)%5][c1];
      encB = matrix[(r2+1)%5][c2];
    } else { // khác hàng/cột
      encA = matrix[r1][c2];
      encB = matrix[r2][c1];
    }

    cipher += encA + encB;
    logDetail.push(`${a}${b} → ${encA}${encB}`);
  }

  showResult(matrix, preprocessPlain(input), logDetail, cipher, 'Mã hóa');
}

// ------------------ Decrypt ------------------
function decryptPlayfair(){
  let input = document.getElementById("plain").value;
  let key = document.getElementById("key").value;
  let err = validateInput(input,key);
  if(err){showError(err); return;}

  let matrix = makeMatrix(key);
  let text = input.toUpperCase().replace(/J/g,'I').replace(/[^A-Z]/g,'');
  let plain='';
  let logDetail=[];

  for(let i=0;i<text.length;i+=2){
    let a=text[i], b=text[i+1];
    let [r1,c1]=findPos(matrix,a);
    let [r2,c2]=findPos(matrix,b);
    let decA, decB;

    if(r1===r2){ // cùng hàng
      decA = matrix[r1][(c1+4)%5];
      decB = matrix[r2][(c2+4)%5];
    } else if(c1===c2){ // cùng cột
      decA = matrix[(r1+4)%5][c1];
      decB = matrix[(r2+4)%5][c2];
    } else { // khác hàng/cột
      decA = matrix[r1][c2];
      decB = matrix[r2][c1];
    }

    plain += decA + decB;
    logDetail.push(`${a}${b} → ${decA}${decB}`);
  }

  showResult(matrix, text.match(/.{1,2}/g).join(', '), logDetail, plain, 'Giải mã');
}

// ------------------ Show Result ------------------
function showResult(matrix,digraphs,logDetail,result,type){
  document.getElementById("stepsBox").style.display="block";
  document.getElementById("log1").innerHTML=`<b>Ma trận khóa:</b><br>${matrix.map(r=>r.join(' ')).join('<br>')}`;
  document.getElementById("log2").innerHTML=`<b>Digraphs:</b><br>${digraphs}`;
  document.getElementById("log3").innerHTML=`<b>${type}:</b><br>${logDetail.join('<br>')}`;
  document.getElementById("final").innerHTML=`<div class="result">Kết quả ${type.toLowerCase()}: <b>${result}</b></div>`;
}

// ------------------ Error ------------------
function showError(msg){
  document.getElementById("stepsBox").style.display="block";
  document.getElementById("log1").innerHTML=`<div class="error">${msg}</div>`;
  document.getElementById("log2").innerHTML="";
  document.getElementById("log3").innerHTML="";
  document.getElementById("final").innerHTML="";
}
