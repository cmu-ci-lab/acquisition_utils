function H = compute_affinity(m,M);

%compute_affinity
%
%[H,Hnorm,inv_Hnorm] = compute_homography(m,M)
%
%Computes the planar homography between the point coordinates on the plane (M) and the image
%point coordinates (m).
%
%INPUT: m: homogeneous coordinates in the image plane (3xN matrix)
%       M: homogeneous coordinates in the plane in 3D (3xN matrix)
%
%OUTPUT: H: Affinity matrix (3x3 homogeneous matrix)
%
%Definition: m ~ H*M where "~" means equal up to a non zero scalar factor.
%
%Method: Computes the affinity through quasi-linear method.

if (size(m, 1) < 3),
   m = in2hom(m);
end;

if (size(M, 1) < 3),
	M = in2hom(M);
end;

m = normhom(m);
M = normhom(M);

H = getAffinityDLT(m, M);
H = H / H(end);

% if numPoints > 4,
%    
%    % Final refinement:
%    hhv = reshape(H',9,1);
%    hhv = hhv(1:8);
%    
%    for iter=1:10,
%       
% 
%    
% 		mrep = H * M;
% 
% 		J = zeros(2*numPoints,8);
% 
% 		MMM = (M ./ (ones(3,1)*mrep(3,:)));
% 
% 		J(1:2:2*numPoints,1:3) = -MMM';
% 		J(2:2:2*numPoints,4:6) = -MMM';
% 		
% 		mrep = mrep ./ (ones(3,1)*mrep(3,:));
% 
% 		m_err = m(1:2,:) - mrep(1:2,:);
% 		m_err = m_err(:);
% 
% 		MMM2 = (ones(3,1)*mrep(1,:)) .* MMM;
% 		MMM3 = (ones(3,1)*mrep(2,:)) .* MMM;
% 
% 		J(1:2:2*numPoints,7:8) = MMM2(1:2,:)';
% 		J(2:2:2*numPoints,7:8) = MMM3(1:2,:)';
% 
% 		MMM = (M ./ (ones(3,1)*mrep(3,:)))';
% 
% 		hh_innov  = inv(J'*J)*J'*m_err;
% 
% 		hhv_up = hhv - hh_innov;
% 
% 		H_up = reshape([hhv_up;1],3,3)';
% 
% 		%norm(m_err)
% 		%norm(hh_innov)
% 
% 		hhv = hhv_up;
%       H = H_up;
%       
%    end;
%    
% 
% end;
