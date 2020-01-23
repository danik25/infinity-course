angular.module("myapp", [])
    .controller("myController", function($scope) {
		$scope.currencies = ["NIS", "EURO", "DOLLAR"];
		$scope.result = 0
		$scope.convertAmount = function(selectedName, amount){
			if(selectedName == "EURO")
			{
				$scope.result = amount * 3.8
			}
			if(selectedName == "DOLLAR")
			{
				$scope.result = amount * 3.4
			}
			else{
				$scope.result = amount
			}
		};
} );