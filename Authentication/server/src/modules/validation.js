export function checkEmailFormat(exp) {
	const regExp = /^[0-9a-zA-Z]([-_\.]?[0-9a-zA-Z])*@[0-9a-zA-Z]([-_\.]?[0-9a-zA-Z])*\.[a-zA-Z]{2,3}$/i;
	return regExp.test(exp);	
}

export function checkUsernameFormat(exp) {
	const regExp = /^[a-z0-9]+$/;
	return regExp.test(exp); 
}

export function checkPasswordFormat(exp) {
	const regExp = /^(?=.*[a-zA-Z])(?=.*[0-9])[a-zA-Z0-9!@#$%^&*]{8,20}$/;
	return regExp.test(exp);
}