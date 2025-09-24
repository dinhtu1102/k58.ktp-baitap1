function caesarShift(text, key, encrypt = true) {
    key = parseInt(key);
    if (!encrypt) key = -key;
    let result = "";

    text = text.toUpperCase();

    for (let i = 0; i < text.length; i++) {
        let char = text[i];
        if (char >= 'A' && char <= 'Z') {
            let code = ((char.charCodeAt(0) - 65 + key + 26) % 26) + 65;
            result += String.fromCharCode(code);
        } else {
            result += char; // giữ nguyên ký tự không phải chữ
        }
    }
    return result;
}

function encrypt() {
    let text = document.getElementById("text").value;
    let key = document.getElementById("key").value;
    document.getElementById("result").value = caesarShift(text, key, true);
}

function decrypt() {
    let text = document.getElementById("text").value;
    let key = document.getElementById("key").value;
    document.getElementById("result").value = caesarShift(text, key, false);
}
