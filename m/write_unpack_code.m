function [msg_unpack_s, def_s, dcl_s] = write_unpack_code
    % parse dbc
    DBC_O = dbc_unpack_to_c('ME5_APSPA.DBC');

    % read config: canid, signal_name
    config = upack_config;

    % 
    unique_canids = unique(cell2mat(config(:,1)));
    len_unique_canids = length(unique_canids);
    msg_unpack_all = cell(len_unique_canids,1);
    def_all = cell(len_unique_canids,1);
    dcl_all = cell(len_unique_canids,1);

    %
    for i=1:len_unique_canids
        % unique canid
        unique_canid = unique_canids(i);

        % cfg
        idxs_cfg = find([config{:,1}]==unique_canid);
        signal_names_cfg = config(idxs_cfg,2);

        % dbc
        idx_msg = find([DBC_O{:,2}]==unique_canid);
        signal_infos_dbc = DBC_O{idx_msg, 3};

        % 
        [flag, idx_sig_pre] = ismember(signal_names_cfg, signal_infos_dbc(:,1));
        idx_sig = idx_sig_pre(flag);
        signal_infos = {signal_infos_dbc(idx_sig, 1), signal_infos_dbc(idx_sig, 2)} ;

        sig_unpack = cellfun(@genOneUnapck, signal_infos{1}, signal_infos{2},...
            'UniformOutput', false);
        msg_unpack = strjoin(sig_unpack, newline);
        msg_unpack_with_cond = genMsgCond(unique_canid, msg_unpack);

        [dcl, def] = genDD(signal_infos{1});

        msg_unpack_all{i} = msg_unpack_with_cond;
        def_all{i} = def;
        dcl_all{i} = dcl;
    end

    msg_unpack_s = strjoin(msg_unpack_all, newline);
    def_s = strjoin(def_all, newline);
    dcl_s = strjoin(dcl_all, newline);
end


function l = genOneUnapck(n, p)
    l = sprintf('    %s=%s;', n, p);
end


function l = genMsgCond(canid, msg_unpack)
    l_s = sprintf('if(gcanid==0x%X) {', canid);
    l_e = sprintf('}');
    l = strjoin({l_s, msg_unpack, l_e, newline}, newline);
end


function [dcl, def] = genDD(ns)
    dclpre = cellfun(@gendcl, ns, 'UniformOutput', false);
    dcl = strjoin(dclpre, '\n');
    defpre = cellfun(@gendef, ns, 'UniformOutput', false);
    def = strjoin(defpre, '\n');
end

function l = gendcl(n)
    l = sprintf('extern float %s;',n);
end

function l = gendef(n)
    l = sprintf('float %s=0.0F;',n);
end

