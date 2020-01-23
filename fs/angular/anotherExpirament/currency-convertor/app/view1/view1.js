'use strict';

angular.module('myApp.view1', ['ngRoute'])

.config(['$routeProvider', function($routeProvider) {
  $routeProvider.when('/view1', {
    templateUrl: 'view1/view1.html',
    styleUrls: ['view1.css'],
    controller: 'View1Ctrl'
  });
}])

.controller('View1Ctrl', ['$scope', function($scope) {
    $scope.currencies = ["NIS", "EURO", "DOLLAR"];
    $scope.mult = [1, 3.8, 3.4];
    $scope.img = ['https://previews.123rf.com/images/nikiteev/nikiteev1905/nikiteev190500093/123328789-vector-cartoon-gold-israeli-currency-symbol-shekel-sign-.jpg', 
    'https://previews.123rf.com/images/nikiteev/nikiteev1811/nikiteev181100144/127414079-vector-gold-cartoon-currency-sign-euro-money-symbol.jpg',
    'https://st4.depositphotos.com/2485347/22819/v/1600/depositphotos_228194434-stock-illustration-cartoon-gold-currency-sign-dollar.jpg'];
    $scope.result = 0
    $scope.imgSrc = {}
		$scope.convertAmount = function(selectedName, amount){
      $scope.result = amount * $scope.mult[$scope.currencies.indexOf(selectedName)]
      $scope.imgSrc = $scope.img[$scope.currencies.indexOf(selectedName)]
		};
}]);