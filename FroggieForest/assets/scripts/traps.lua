traps =
{
    trap1 = {
        components = {

            sprite = {
                assetId = "trap1",
                width = 32,
                height = 32,
                src_rect = {x = 0, y = 0},
                z_index = 1,
            },

            animation = {
                num_frames = 1,
                speed_rate = 1,
                is_loop = true,
            },

            rigid_body = {
                is_dynamic = false,
                is_solid = false,
                mass = 0,
            },

            box_collider = {
                width = 32,
                height = 32,
                offset = {x = 0, y = 0},
            },

            tag = {
                tag = "trap",
            },

            transform = {
                position = {x = 0, y = 0},
                scale = {x = 1.0, y = 1.0},
                rotation = 0.0,
            },
        },
    },
}