function submitCompany(){
	var data = {};
	
	data.companyName = document.getElementById("companyNameCR").value;
	$.post("http://localhost:8081/IOTTomcatServer/CR", JSON.stringify(data), function(result){
	    $("span").html(result);
	  });
}
function submitProduct(){
	var data = {};
	
	data.companyName = document.getElementById("companyNamePR").value;
	data.productName = document.getElementById("productNamePR").value;
	$.post("http://localhost:8081/IOTTomcatServer/PR", JSON.stringify(data), function(result){
	    $("span").html(result);
	  });
}