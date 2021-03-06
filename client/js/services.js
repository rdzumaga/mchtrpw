/// @file services.js
/// @brief AngularJS services, AJAX communication with the server

angular.module('myAppServices', [])
    .service('srvInfo', //current information from zsm server
             function($http) {
                 this.baseURL = client_server_prefix + '/ajax/'; //the prefix defined in version.js

                 this.getVersion = function(callback) {
                     return $http.get(this.baseURL + 'version/get').success(callback);
				 };
                 this.getCurrent = function(callback) {
                     return $http.get(this.baseURL + 'current/get').success(callback);
                 };
                 this.getCppNumber = function(callback) {
                     return $http.get(this.baseURL + 'calcpy/getNumber').success(callback);
                 };

             });
