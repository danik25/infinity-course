function submitCompany(){
	var data = {};
	
	data.companyName = document.getElementById("companyNameCR").value;
	$.post("http://localhost:8080/newProject/CR", JSON.stringify(data), function(result){
	    $("span").html(result);
	  });
}
function submitProduct(){
	var data = {};
	
	data.companyName = document.getElementById("companyNamePR").value;
	data.productName = document.getElementById("productNamePR").value;
	$.post("http://localhost:8080/newProject/PR", JSON.stringify(data), function(result){
	    $("span").html(result);
	  });
}

function submitLogin(){
	var data = {};
    
    data.password = document.getElementById("passwordLOGIN").value;
	data.companyName = document.getElementById("companyNameLOGIN").value;
	
	var answer = $.post("http://localhost:8080/newProject/HOME", JSON.stringify(data), function(result){
		alert( "success" );
      });
      
    console.log(answer);
}
