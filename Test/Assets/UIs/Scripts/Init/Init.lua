
post_load_funcs = {}
next_post_load_index = 0

function PushPostLoadFunc(func)
    post_load_funcs[next_post_load_index] = func
    next_post_load_index = next_post_load_index + 1
end

function FinalizeLoad()
    load_funcs = post_load_funcs
    post_load_funcs = {}
    next_post_load_index = 0

    for k, v in pairs(load_funcs) do
        v()
    end
end

